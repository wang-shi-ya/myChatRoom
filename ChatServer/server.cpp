// server.cpp
#include "server.h"
#include "clienthandler.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);

    if(!db.connect()) {
        qDebug() << "Failed to connect to database";
    }
}

Server::~Server()
{
    tcpServer->close();
    qDeleteAll(clients);
}

bool Server::start(quint16 port)
{
    if(!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start:" << tcpServer->errorString();
        return false;
    }
    qDebug() << "Server started on port" << port;
    return true;
}

void Server::newConnection()
{
    while (tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = tcpServer->nextPendingConnection();

        bool alreadyExists = false;
        for (ClientHandler *client : clients) {
            if (client->getSocketDescriptor() == socket->socketDescriptor()) {
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists) {
            ClientHandler *client = new ClientHandler(socket, this);
            connect(client, &ClientHandler::clientDisconnected, this, &Server::clientDisconnected);
            clients.append(client);
            qDebug() << "New client connected. Total clients:" << clients.size();
        } else {
            qDebug() << "Duplicate connection attempt for socket" << socket->socketDescriptor();
            socket->close();
            socket->deleteLater();
        }
    }
}

void Server::clientDisconnected(ClientHandler *client)
{
    if(client->getAccount() != -1) {
        QString username = db.getUsername(client->getAccount());
        broadcastUserOffline(client->getAccount(), username);
    }

    clients.removeOne(client);
    client->deleteLater();
    qDebug() << "Client disconnected. Total clients:" << clients.size();
}

void Server::broadcastMessage(const QJsonObject &message, ClientHandler *exclude)
{
    for(ClientHandler *client : clients) {
        if(client != exclude) {
            client->sendMessage(message);
        }
    }
}

void Server::broadcastUserOnline(int account, const QString &username)
{
    QJsonObject message;
    message["type"] = "user_online";
    message["account"] = account;
    message["username"] = username;
    broadcastMessage(message);
}

void Server::broadcastUserOffline(int account, const QString &username)
{
    QJsonObject message;
    message["type"] = "user_offline";
    message["account"] = account;
    message["username"] = username;
    broadcastMessage(message);
}

void Server::sendOnlineUsers(ClientHandler *client)
{
    QJsonObject message;
    message["type"] = "online_users";
    QJsonArray users;

    for(ClientHandler *c : clients) {
        if(c->getAccount() != -1 && c != client) {
            QJsonObject user;
            user["account"] = c->getAccount();
            user["username"] = db.getUsername(c->getAccount());
            users.append(user);
        }
    }

    message["users"] = users;
    client->sendMessage(message);
}
