// client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    bool isConnected() const;

    void login(int account, const QString &password);
    void registerUser(int account, const QString &username, const QString &password);
    void sendChatMessage(const QString &content, int target = 0, bool isImage = false);

    // 新增：通用 JSON 发送 & 拉取历史
    void sendRaw(const QJsonObject &obj);
    void requestHistory(int target);

    //修改信息
    void updateUsername(const QString &newUsername);
    void updatePassword(const QString &oldPassword, const QString &newPassword);
    int getAccount() const { return account; }
    QString getUsername() const { return username; }

signals:
    void connected();
    void disconnected();
    void loginSuccess(int account, const QString &username);
    void loginFailed(const QString &error);
    void registerSuccess();
    void registerFailed(const QString &error);

    void usernameUpdated(const QString &newUsername);
    void usernameUpdateFailed();
    void passwordUpdated();
    void passwordUpdateFailed();

    // 新增：包含 target 的消息
    void newMessage(int sender, const QString &username, const QString &content, bool isImage, const QString &timestamp, int target);

    void userOnline(int account, const QString &username);
    void userOffline(int account, const QString &username);
    void onlineUsersReceived(const QList<QPair<int, QString>> &users);

    // 历史记录响应
    void historyReceived(int target, const QJsonArray &messages);
    // 被踢下线信号
    void forcedLogout(const QString &reason);
private slots:
    void readyRead();
    void onConnected();
    void onDisconnected();

private:
    QTcpSocket *socket;
    int account;
    QString username;
    QByteArray buffer;
    void processMessage(const QJsonObject &message);
};

#endif // CLIENT_H
