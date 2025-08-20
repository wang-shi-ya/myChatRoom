#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include "client.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(Client *client, QWidget *parent = nullptr);
    ~ChatWindow();
    void appendTextMessage(const QString &sender, const QString &message, bool isOwn);
    void appendImageMessage(const QString &sender, const QString &imagePath, bool isOwn);

private slots:
    void onSendClicked();
    void onEditProfileClicked();

    // 仅用于“接收别人消息”的信号槽
    void onNewMessage(int sender, const QString &username, const QString &content, bool isImage, const QString &timestamp);

    void onUserOnline(int account, const QString &username);
    void onUserOffline(int account, const QString &username);
    void onOnlineUsersReceived(const QList<QPair<int, QString>> &users);
    void onDisconnected();

    // 历史记录
    void onHistoryReceived(int target, const QJsonArray &messages);

    // 切换会话目标
    void onTargetChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void showImageDialog(const QString &base64);

private:
    Ui::ChatWindow *ui;
    Client *client;
    QLineEdit *inputEdit;     // 输入框
    int currentTargetAccount = 0; // 0=群聊；否则=选中的私聊账号

    void appendMessage(const QString &username, const QString &message, const QString &timestamp, bool isSelf = false);
    void appendImageMessage(const QString &username, const QString &base64, const QString &timestamp, bool isSelf = false);
    void appendSystemMessage(const QString &message);

    int parseAccountFromItem(QListWidgetItem *item) const;
    void refreshTargetAndLoadHistory(); // 根据当前选择刷新 currentTargetAccount，并请求历史
    void ensureAllItemOnTop(); // 确保“所有人(0)”在列表顶部
};

#endif // CHATWINDOW_H
