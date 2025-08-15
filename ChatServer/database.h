// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool connect();
    bool registerUser(int account, const QString &username, const QString &password);
    bool login(int account, const QString &password);
    QString getUsername(int account);
    bool isUserOnline(int account);

    // 新增：消息存取
    bool saveMessage(int sender, int target, const QString &content, bool isImage);
    QJsonArray getHistoryFor(int requester, int target, int limit = 100); // 返回 JSON 数组

    //新增：信息修改
    bool updateUsername(int account, const QString &newUsername);
    bool updatePassword(int account, const QString &newPassword);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
