// chatwindow.cpp
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "ProfileDialog.h"
#include <QDateTime>
#include <QMessageBox>

static const char* kAllLabel = "所有人 (0)";

ChatWindow::ChatWindow(Client *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
    , client(client)
{
    ui->setupUi(this);

    setWindowTitle(QString("聊天室 - %1 (账号: %2)").arg(client->getUsername()).arg(client->getAccount()));

    // 顶部插入“所有人(0)”
    ensureAllItemOnTop();
    ui->onlineList->setCurrentRow(0); // 默认选中群聊

    //发送信息
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::onSendClicked);
    //修改资料
    connect(ui->editProfileButton, &QPushButton::clicked,this, &ChatWindow::onEditProfileClicked);

    //重复登录提出消息
    connect(client, &Client::forcedLogout, this, [this](const QString &reason){
        QMessageBox::warning(this, "被踢下线", reason);
        this->close();
    });

    // newMessage 含 target
    connect(client, &Client::newMessage, this, &ChatWindow::onNewMessage);
    connect(client, &Client::userOnline, this, &ChatWindow::onUserOnline);
    connect(client, &Client::userOffline, this, &ChatWindow::onUserOffline);
    connect(client, &Client::onlineUsersReceived, this, &ChatWindow::onOnlineUsersReceived);
    connect(client, &Client::disconnected, this, &ChatWindow::onDisconnected);

    // 历史记录
    connect(client, &Client::historyReceived, this, &ChatWindow::onHistoryReceived);

    // 切换会话对象时，请求相应历史
    connect(ui->onlineList, &QListWidget::currentItemChanged, this, &ChatWindow::onTargetChanged);

    appendSystemMessage("欢迎进入聊天室！");

    // 首次加载群聊历史
    refreshTargetAndLoadHistory();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::ensureAllItemOnTop()
{
    if (ui->onlineList->count() == 0 || ui->onlineList->item(0)->text() != kAllLabel) {
        ui->onlineList->insertItem(0, kAllLabel);
    }
}

int ChatWindow::parseAccountFromItem(QListWidgetItem *item) const
{
    if (!item) return 0;
    const QString text = item->text();
    if (text == kAllLabel) return 0;
    int l = text.lastIndexOf("(");
    int r = text.lastIndexOf(")");
    if (l != -1 && r != -1 && r > l) {
        return text.mid(l+1, r-l-1).toInt();
    }
    return 0;
}

void ChatWindow::refreshTargetAndLoadHistory()
{
    currentTargetAccount = parseAccountFromItem(ui->onlineList->currentItem());
    client->requestHistory(currentTargetAccount);
}

void ChatWindow::onSendClicked()//发送消息
{
    QString message = ui->messageEdit->toPlainText();
    if(message.isEmpty()) return;

    client->sendChatMessage(message, currentTargetAccount);
    appendMessage("You",
                  message,
                  QDateTime::currentDateTime().toString("hh:mm:ss"),
                  true);
    ui->messageEdit->clear();
}

void ChatWindow::onNewMessage(int sender, const QString &username, const QString &content, bool isImage, const QString &timestamp, int target)
{
    Q_UNUSED(isImage);

    // 只显示当前会话相关消息
    const int self = client->getAccount();

    bool related = false;
    if (currentTargetAccount == 0) {
        // 群聊视图：只看群聊消息
        related = (target == 0);
    } else {
        // 私聊视图：双方互发
        related = ((target == currentTargetAccount && sender == self) ||
                   (sender == currentTargetAccount && target == self));
    }
    if (!related) return;

    const bool isSelf = (sender == self);
    const QString name = isSelf ? "You" : username;
    const QString timeStr = QDateTime::fromString(timestamp, Qt::ISODate).toString("hh:mm:ss");
    appendMessage(name, content, timeStr, isSelf);
}

void ChatWindow::onUserOnline(int account, const QString &username)
{
    // 如果不存在则添加
    ensureAllItemOnTop();
    bool exists = false;
    for (int i=1;i<ui->onlineList->count();++i) {
        if (parseAccountFromItem(ui->onlineList->item(i)) == account) {
            exists = true; break;
        }
    }
    if (!exists) {
        ui->onlineList->addItem(QString("%1 (%2)").arg(username).arg(account));
    }
    appendSystemMessage(QString("%1 进入聊天室").arg(username));
}

void ChatWindow::onUserOffline(int account, const QString &username)
{
    for (int i=1;i<ui->onlineList->count();++i) {
        if (parseAccountFromItem(ui->onlineList->item(i)) == account) {
            delete ui->onlineList->takeItem(i);
            break;
        }
    }
    appendSystemMessage(QString("%1 离开聊天室").arg(username));
}

void ChatWindow::onOnlineUsersReceived(const QList<QPair<int, QString>> &users)
{
    // 先保留第0项“所有人(0)”，清理其他
    ensureAllItemOnTop();
    while (ui->onlineList->count() > 1) {
        delete ui->onlineList->takeItem(1);
    }
    for(const auto &user : users) {
        ui->onlineList->addItem(QString("%1 (%2)").arg(user.second).arg(user.first));
    }
}

void ChatWindow::onHistoryReceived(int target, const QJsonArray &messages)
{
    // 若返回的不是当前会话的历史，则忽略（避免异步竞争）
    if (target != currentTargetAccount) return;

    // 替换当前聊天区为历史（保持简单：每次切换目标就刷新）
    ui->chatView->clear();
    appendSystemMessage(target == 0 ? "—— 群聊历史 ——" : "—— 私聊历史 ——");

    const int self = client->getAccount();

    for (const auto &v : messages) {
        const QJsonObject obj = v.toObject();
        int sender = obj["sender"].toInt();
        QString content = obj["content"].toString();
        bool isImage = obj["isImage"].toBool();
        QString timestamp = obj["timestamp"].toString();

        Q_UNUSED(isImage); // 如需图片消息可在此扩展

        bool isSelf = (sender == self);
        QString name = isSelf ? "You" : (sender == self ? "You" : obj.contains("username") ? obj["username"].toString() : QString::number(sender));
        // 若数据库未存用户名，可仅用账号；为一致性，我们用账号替代
        if (!isSelf && name == "You") name = QString::number(sender);

        QString timeStr = QDateTime::fromString(timestamp, Qt::ISODate).toString("hh:mm:ss");
        appendMessage(name, content, timeStr, isSelf);
    }
}

void ChatWindow::onDisconnected()
{
    QMessageBox::critical(this, "Disconnected", "You have been disconnected from the server");
    close();
}

void ChatWindow::appendMessage(const QString &username, const QString &message, const QString &timestamp, bool isSelf)
{
    QString color = isSelf ? "blue" : "green";
    QString align = isSelf ? "right" : "left";

    QString html = QString("<div style='margin: 5px; text-align: %1;'>"
                           "<span style='color: %2; font-weight: bold;'>%3</span> "
                           "<span style='color: gray; font-size: small;'>[%4]</span><br>"
                           "<span>%5</span>"
                           "</div>")
                       .arg(align)
                       .arg(color)
                       .arg(username)
                       .arg(timestamp)
                       .arg(message);

    ui->chatView->append(html);
}

void ChatWindow::appendSystemMessage(const QString &message)
{
    QString html = QString("<div style='margin: 5px; text-align: center; color: gray;'>%1</div>").arg(message);
    ui->chatView->append(html);
}

void ChatWindow::onTargetChanged(QListWidgetItem *current, QListWidgetItem * /*previous*/)
{
    Q_UNUSED(current);
    refreshTargetAndLoadHistory();
}
void ChatWindow::onEditProfileClicked()
{
    ProfileDialog dlg(client, this);
    dlg.exec(); // 模态对话框
}
