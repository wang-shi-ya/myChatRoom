// server.h
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>
#include <QJsonObject>
#include "database.h"

class ClientHandler;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    bool start(quint16 port);
    Database* database() { return &db; }

    void broadcastMessage(const QJsonObject &message, ClientHandler *exclude = nullptr);
    void broadcastUserOnline(int account, const QString &username);
    void broadcastUserOffline(int account, const QString &username);
    void sendOnlineUsers(ClientHandler *client);

    // 新增：访问当前客户端列表（用于定向私聊发送）
    QList<ClientHandler*> clientsList() const { return clients; }

private slots:
    void newConnection();
    void clientDisconnected(ClientHandler *client);

private:
    QTcpServer *tcpServer;
    QList<ClientHandler*> clients;
    Database db;
};

#endif // SERVER_H
