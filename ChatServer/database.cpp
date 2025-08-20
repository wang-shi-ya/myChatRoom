#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    if (!QSqlDatabase::isDriverAvailable("QMYSQL")) {
        qDebug() << "MySQL driver not available";
        qDebug() << "Available drivers:" << QSqlDatabase::drivers();
        return;
    }
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("chatroom");
    db.setUserName("root");
    db.setPassword("HBsc75820306@");
}

Database::~Database()
{
    if(db.isOpen()) {
        db.close();
    }
}

bool Database::connect()
{
    if(!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}

bool Database::registerUser(int account, const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO user (account, username, password, createTime) "
                  "VALUES (:account, :username, :password, NOW())");
    query.bindValue(":account", account);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if(!query.exec()) {
        qDebug() << "Register error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::login(int account, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM user WHERE account = :account");
    query.bindValue(":account", account);
    if(!query.exec() || !query.next()) {
        return false;
    }
    QString storedPassword = query.value(0).toString();
    return storedPassword == password;
}

QString Database::getUsername(int account)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM user WHERE account = :account");
    query.bindValue(":account", account);
    if(!query.exec() || !query.next()) {
        return QString();
    }
    return query.value(0).toString();
}

bool Database::isUserOnline(int /*account*/)
{
    return false;
}

bool Database::saveMessage(int sender, int target, const QString &content, bool isImage)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (sender, target, content, isImage) "
                  "VALUES (:sender, :target, :content, :isImage)");
    query.bindValue(":sender", sender);
    query.bindValue(":target", target);
    query.bindValue(":content", content);
    query.bindValue(":isImage", isImage);
    if(!query.exec()) {
        qDebug() << "saveMessage error:" << query.lastError().text();
        return false;
    }
    return true;
}

QJsonArray Database::getHistoryFor(int requester, int target, int limit)
{
    QJsonArray arr;
    QSqlQuery query;
    if (target == 0) {
        // 群聊：JOIN user 取 username
        query.prepare(
            "SELECT m.sender, m.target, m.content, m.isImage, m.timestamp, u.username "
            "FROM messages m "
            "JOIN user u ON m.sender = u.account "
            "WHERE m.target = 0 "
            "ORDER BY m.id DESC LIMIT :limit"
            );
        query.bindValue(":limit", limit);
    } else {
        // 私聊：双向 + JOIN user
        query.prepare(
            "SELECT m.sender, m.target, m.content, m.isImage, m.timestamp, u.username "
            "FROM messages m "
            "JOIN user u ON m.sender = u.account "
            "WHERE (m.sender = :req AND m.target = :tar) "
            "   OR (m.sender = :tar AND m.target = :req) "
            "ORDER BY m.id DESC LIMIT :limit"
            );
        query.bindValue(":req", requester);
        query.bindValue(":tar", target);
        query.bindValue(":limit", limit);
    }

    if(query.exec()) {
        while(query.next()) {
            QJsonObject obj;
            obj["sender"]    = query.value(0).toInt();
            obj["target"]    = query.value(1).toInt();
            obj["content"]   = query.value(2).toString();
            obj["isImage"]   = query.value(3).toBool();
            obj["timestamp"] = query.value(4).toString();
            obj["username"]  = query.value(5).toString();
            arr.append(obj);
        }
    } else {
        qDebug() << "getHistoryFor error:" << query.lastError().text();
    }
    return arr;
}

bool Database::updateUsername(int account, const QString &newUsername)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET username = :username WHERE account = :account");
    query.bindValue(":username", newUsername);
    query.bindValue(":account", account);

    if (!query.exec()) {
        qDebug() << "Update username error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updatePassword(int account, const QString &newPassword)
{
    QSqlQuery query;
    query.prepare("UPDATE user SET password = :password WHERE account = :account");
    query.bindValue(":password", newPassword);
    query.bindValue(":account", account);

    if (!query.exec()) {
        qDebug() << "Update password error:" << query.lastError().text();
        return false;
    }
    return true;
}
