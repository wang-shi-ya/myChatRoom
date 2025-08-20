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

    // 通用 JSON & 历史
    void sendRaw(const QJsonObject &obj);
    void requestHistory(int target);

    // 修改信息
    void updateUsername(const QString &newUsername);
    void updatePassword(const QString &oldPassword, const QString &newPassword);
    int getAccount() const { return account; }
    QString getUsername() const { return username; }

    // 发送图片（已去掉“发文件”）
    void sendImage(const QString &filePath, int target = 0);

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

    // 不再带 filename
    void newMessage(int sender, const QString &username, const QString &content, bool isImage, const QString &timestamp);

    void userOnline(int account, const QString &username);
    void userOffline(int account, const QString &username);
    void onlineUsersReceived(const QList<QPair<int, QString>> &users);

    void historyReceived(int target, const QJsonArray &messages);
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
