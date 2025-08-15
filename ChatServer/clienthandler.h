#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

class Server;

class ClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientHandler(QTcpSocket *socket, Server *server, QObject *parent = nullptr);
    ~ClientHandler();

    void sendMessage(const QJsonObject &message);
    int getAccount() const { return account; }
    int getSocketDescriptor() const { return socket->socketDescriptor(); }

signals:
    void clientDisconnected(ClientHandler *client);

private slots:
    void onReadyRead();
    void onSocketDisconnected();

private:
    QByteArray buffer;
    QTcpSocket *socket;
    Server *server;
    int account;
    QString username;

    void processMessage(const QJsonObject &message);
    void handleLogin(const QJsonObject &message);
    void handleRegister(const QJsonObject &message);
    void handleChatMessage(const QJsonObject &message);
    void handleGetHistory(const QJsonObject &message);
    void handleUpdatePassword(const QJsonObject &message);
    void handleUpdateUsername(const QJsonObject &message);
    void disconnectSocket() {
        if (socket && socket->state() == QTcpSocket::ConnectedState) {
            socket->disconnectFromHost();
        }
    }

};

#endif // CLIENTHANDLER_H
