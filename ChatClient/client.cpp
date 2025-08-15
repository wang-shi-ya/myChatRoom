// client.cpp
#include "client.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), account(-1)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead);
}

Client::~Client()
{
    disconnectFromServer();
    socket->deleteLater();
}

bool Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    return socket->waitForConnected(3000);
}

void Client::disconnectFromServer()
{
    if(socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

bool Client::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

void Client::readyRead()
{
    buffer.append(socket->readAll());
    while (true) {
        int newlineIndex = buffer.indexOf('\n');
        if (newlineIndex == -1) break;

        QByteArray jsonData = buffer.left(newlineIndex);
        buffer.remove(0, newlineIndex + 1);

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << error.errorString();
            continue;
        }
        processMessage(doc.object());
    }
}

void Client::onConnected()
{
    emit connected();
}

void Client::onDisconnected()
{
    emit disconnected();
}

void Client::processMessage(const QJsonObject &message)
{
    const QString type = message["type"].toString();

    if(type == "login_response") {
        bool success = message["success"].toBool();
        if(success) {
            account = message["account"].toInt();
            username = message["username"].toString();
            emit loginSuccess(account, username);
        } else {
            emit loginFailed(message["error"].toString());
        }
    } else if(type == "register_response") {
        bool success = message["success"].toBool();
        if(success) {
            emit registerSuccess();
        } else {
            emit registerFailed(message["error"].toString());
        }
    } else if(type == "chat") {
        int sender = message["sender"].toInt();
        QString uname = message["username"].toString();
        QString content = message["content"].toString();
        bool isImage = message["isImage"].toBool();
        QString timestamp = message["timestamp"].toString();
        int target = message["target"].toInt();

        emit newMessage(sender, uname, content, isImage, timestamp, target);
    } else if(type == "user_online") {
        int acc = message["account"].toInt();
        QString uname = message["username"].toString();
        emit userOnline(acc, uname);
    } else if(type == "user_offline") {
        int acc = message["account"].toInt();
        QString uname = message["username"].toString();
        emit userOffline(acc, uname);
    } else if(type == "online_users") {
        QList<QPair<int, QString>> users;
        QJsonArray userArray = message["users"].toArray();
        for(const QJsonValue &value : userArray) {
            QJsonObject user = value.toObject();
            users.append(qMakePair(user["account"].toInt(), user["username"].toString()));
        }
        emit onlineUsersReceived(users);
    } else if (type == "history") {
        int target = message["target"].toInt();
        QJsonArray msgs = message["messages"].toArray();
        emit historyReceived(target, msgs);
    }
    else if (type == "force_logout") {
        QString reason = message["reason"].toString();
        emit forcedLogout(reason);
    }else if (type == "update_username_response") {
        bool success = message["success"].toBool();
        if (success) {
            username = message["newUsername"].toString();
            emit usernameUpdated(username);
        } else {
            emit usernameUpdateFailed();
        }
    } else if (type == "update_password_response") {
        bool success = message["success"].toBool();
        if (success) {
            emit passwordUpdated();
        } else {
            emit passwordUpdateFailed();
        }
    }


}

void Client::login(int account, const QString &password)
{
    QJsonObject message;
    message["type"] = "login";
    message["account"] = account;
    message["password"] = password;
    sendRaw(message);
}

void Client::registerUser(int account, const QString &username, const QString &password)
{
    QJsonObject message;
    message["type"] = "register";
    message["account"] = account;
    message["username"] = username;
    message["password"] = password;
    sendRaw(message);
}

void Client::sendChatMessage(const QString &content, int target, bool isImage)
{
    if(account == -1) return;
    QJsonObject message;
    message["type"] = "chat";
    message["content"] = content;
    message["isImage"] = isImage;
    message["target"] = target; // 新增
    sendRaw(message);
}

void Client::sendRaw(const QJsonObject &obj)
{
    socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact) + "\n");
}

void Client::requestHistory(int target)
{
    QJsonObject req;
    req["type"] = "get_history";
    req["target"] = target; // 0=群聊, 否则=对方账号
    sendRaw(req);
}
//修改信息
void Client::updateUsername(const QString &newUsername)
{
    QJsonObject message;
    message["type"] = "update_username";
    message["newUsername"] = newUsername;
    socket->write(QJsonDocument(message).toJson(QJsonDocument::Compact) + "\n");
}

void Client::updatePassword(const QString &newPassword)
{
    QJsonObject message;
    message["type"] = "update_password";
    message["newPassword"] = newPassword;
    socket->write(QJsonDocument(message).toJson(QJsonDocument::Compact) + "\n");
}

