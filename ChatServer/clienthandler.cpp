#include "clienthandler.h"
#include "server.h"
#include "database.h"
#include <QJsonArray>
#include <QDebug>

ClientHandler::ClientHandler(QTcpSocket *socket, Server *server, QObject *parent)
    : QObject(parent), buffer(), socket(socket), server(server), account(-1)
{
    connect(socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientHandler::onSocketDisconnected);
}

ClientHandler::~ClientHandler()
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
    socket->deleteLater();
}

void ClientHandler::onReadyRead()
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

void ClientHandler::onSocketDisconnected()
{
    emit clientDisconnected(this);
}

void ClientHandler::sendMessage(const QJsonObject &message)
{
    socket->write(QJsonDocument(message).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void ClientHandler::processMessage(const QJsonObject &message)
{
    const QString type = message["type"].toString();
    if (type == "login") {
        handleLogin(message);
    } else if (type == "register") {
        handleRegister(message);
    } else if (type == "chat") {
        handleChatMessage(message);
    } else if (type == "get_history") {
        handleGetHistory(message);
    }else if (type == "update_username") {
        handleUpdateUsername(message);
    } else if (type == "update_password") {
        handleUpdatePassword(message);
    }

}

void ClientHandler::handleLogin(const QJsonObject &message)
{
    int acc = message["account"].toInt();
    QString password = message["password"].toString();

    if (server->database()->login(acc, password)) {

        // 检查是否已登录
        ClientHandler *existingClient = nullptr;
        for (ClientHandler *c : server->clientsList()) {
            if (c != this && c->getAccount() == acc) {
                existingClient = c;
                break;
            }
        }

        if (existingClient) {
            // ==== 选择模式 ====
            bool kickOld = true; // true=踢掉旧连接，false=拒绝新连接

            if (kickOld) {
                // 通知旧连接被踢
                QJsonObject kickMsg;
                kickMsg["type"] = "force_logout";
                kickMsg["reason"] = "您的账号已在其他设备登录";
                existingClient->sendMessage(kickMsg);

                existingClient->disconnectSocket(); // 需要在 ClientHandler 添加一个方法主动断开
            } else {
                // 拒绝新连接
                QJsonObject response;
                response["type"] = "login_response";
                response["success"] = false;
                response["error"] = "该账号已在其他设备登录";
                sendMessage(response);
                return;
            }
        }

        // 正常登录流程
        account = acc;
        username = server->database()->getUsername(account);

        QJsonObject response;
        response["type"] = "login_response";
        response["success"] = true;
        response["account"] = account;
        response["username"] = username;
        sendMessage(response);

        server->broadcastUserOnline(account, username);
        server->sendOnlineUsers(this);

    } else {
        QJsonObject response;
        response["type"] = "login_response";
        response["success"] = false;
        response["error"] = "Invalid account or password";
        sendMessage(response);
    }
}


void ClientHandler::handleRegister(const QJsonObject &message)
{
    int acc = message["account"].toInt();
    QString uname = message["username"].toString();
    QString pwd = message["password"].toString();

    if (server->database()->registerUser(acc, uname, pwd)) {
        QJsonObject response;
        response["type"] = "register_response";
        response["success"] = true;
        sendMessage(response);
    } else {
        QJsonObject response;
        response["type"] = "register_response";
        response["success"] = false;
        response["error"] = "Registration failed";
        sendMessage(response);
    }
}

void ClientHandler::handleChatMessage(const QJsonObject &message)
{
    if (account == -1) return; // 未登录

    const QString content = message["content"].toString();
    const bool isImage = message["isImage"].toBool();
    const int target = message["target"].toInt(); // 0=群聊, 否则=对方账号

    // 先入库
    //qDebug() << "DEBUG saveMessage:" << account << target << content << isImage;
    server->database()->saveMessage(account, target, content, isImage);//历史消息存入

    // 构造广播/私发包
    QJsonObject pack;
    pack["type"]      = "chat";
    pack["sender"]    = account;
    pack["username"]  = username;
    pack["content"]   = content;
    pack["isImage"]   = isImage;
    pack["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    pack["target"]    = target;

    if (target == 0) {
        // 群聊：发给除自己以外所有人
        server->broadcastMessage(pack, this);
        // 回显给自己（让自己也看到刚发的群聊，前端已本地追加也可以）
        //sendMessage(pack);
    } else {
      // 私聊：只发给目标用户
        for (ClientHandler *c : server->clientsList()) {
            if (c->getAccount() == target) {
                c->sendMessage(pack);
            }
        }

    }
}

void ClientHandler::handleGetHistory(const QJsonObject &message)
{
    if (account == -1) return;
    const int target = message["target"].toInt();

    QJsonArray arr = server->database()->getHistoryFor(account, target, /*limit*/100);

    // 统一让客户端按时间正序显示：这里返回时做一次反转（数据库是 DESC）
    QJsonArray inOrder;
    for (int i = arr.size() - 1; i >= 0; --i) inOrder.append(arr.at(i));

    QJsonObject resp;
    resp["type"] = "history";
    resp["target"] = target;
    resp["messages"] = inOrder;
    sendMessage(resp);
}

//修改信息
void ClientHandler::handleUpdateUsername(const QJsonObject &message)
{
    if (account == -1) return; // 未登录

    QString newUsername = message["newUsername"].toString();
    if (newUsername.isEmpty()) return;

    if (server->database()->updateUsername(account, newUsername)) {
        username = newUsername; // 更新内存中的用户名

        QJsonObject response;
        response["type"] = "update_username_response";
        response["success"] = true;
        response["newUsername"] = newUsername;
        sendMessage(response);
    } else {
        QJsonObject response;
        response["type"] = "update_username_response";
        response["success"] = false;
        sendMessage(response);
    }
}

void ClientHandler::handleUpdatePassword(const QJsonObject &message)
{
    if (account == -1) return; // 未登录

    QString newPassword = message["newPassword"].toString();
    if (newPassword.isEmpty()) return;

    if (server->database()->updatePassword(account, newPassword)) {
        QJsonObject response;
        response["type"] = "update_password_response";
        response["success"] = true;
        sendMessage(response);
    } else {
        QJsonObject response;
        response["type"] = "update_password_response";
        response["success"] = false;
        sendMessage(response);
    }
}

