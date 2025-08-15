// database.cpp
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
    db.setUserName("root");           // TODO: 替换为你的账号
    db.setPassword("HBsc75820306@");  // TODO: 替换为你的密码
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
    // 需要的话可扩展在线状态记录
    return false;
}

// ---------- 新增：消息存取 ----------
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
        // 群聊
        query.prepare("SELECT sender, target, content, isImage, timestamp "
                      "FROM messages WHERE target = 0 "
                      "ORDER BY id DESC LIMIT :limit");
        query.bindValue(":limit", limit);
    } else {
        // 私聊：requester 与 target 双向
        query.prepare("SELECT sender, target, content, isImage, timestamp "
                      "FROM messages "
                      "WHERE (sender = :req AND target = :tar) "
                      "   OR (sender = :tar AND target = :req) "
                      "ORDER BY id DESC LIMIT :limit");
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
            arr.append(obj);
        }
    } else {
        qDebug() << "getHistoryFor error:" << query.lastError().text();
    }
    return arr;
}
//修改信息
// database.cpp
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

