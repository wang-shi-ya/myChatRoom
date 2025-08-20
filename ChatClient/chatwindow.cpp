    #include "chatwindow.h"
    #include "ui_chatwindow.h"
    #include "ProfileDialog.h"
    #include "ImageLabel.h"
    #include <QTextCursor>
    #include <QTextDocumentFragment>
    #include <QTextBlockFormat>
    #include <QDateTime>
    #include <QMessageBox>
    #include <QFileDialog>
    #include <QPixmap>
    #include <QFile>

    static const char* kAllLabel = "所有人 (0)";

    ChatWindow::ChatWindow(Client *client, QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::ChatWindow)
        , client(client)
    {
        ui->setupUi(this);

        setWindowTitle(QString("聊天室 - %1 (账号: %2)").arg(client->getUsername()).arg(client->getAccount()));

        // 文本发送
        connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::onSendClicked);

        // 发送图片
        connect(ui->sendImageButton, &QPushButton::clicked, this, [this]() {
            QString path = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg *.bmp)");
            if(path.isEmpty()) return;

            // 发送到服务器
            this->client->sendImage(path, currentTargetAccount);

            // 本地立即显示
            QByteArray imageData;
            QFile file(path);
            if(file.open(QIODevice::ReadOnly)) {
                imageData = file.readAll();
                file.close();
                QString base64 = QString::fromUtf8(imageData.toBase64());
                appendImageMessage("You", base64, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), true);
            }
        });

        //点击图片放大
        ui->chatView->setOpenLinks(false);
        connect(ui->chatView, &QTextBrowser::anchorClicked, [this](const QUrl &url) {
            if (url.scheme() == "image") {
                QString base64 = url.toString().mid(8); // 去掉 "image://"
                showImageDialog(base64);
            }
        });
        // 绑定信号槽
        connect(client, &Client::newMessage, this, &ChatWindow::onNewMessage);
        connect(client, &Client::userOnline, this, &ChatWindow::onUserOnline);
        connect(client, &Client::userOffline, this, &ChatWindow::onUserOffline);
        connect(client, &Client::onlineUsersReceived, this, &ChatWindow::onOnlineUsersReceived);
        connect(client, &Client::disconnected, this, &ChatWindow::onDisconnected);

        connect(ui->onlineList, &QListWidget::currentItemChanged, this, &ChatWindow::onTargetChanged);

        ensureAllItemOnTop();
        ui->onlineList->setCurrentRow(0);
        refreshTargetAndLoadHistory();

        appendSystemMessage("欢迎进入聊天室！");
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

    void ChatWindow::onSendClicked()
    {
        QString content = ui->messageEdit->toPlainText().trimmed();
        if(content.isEmpty()) return;

        client->sendChatMessage(content, currentTargetAccount, false);

        appendMessage("You", content, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), true);

        ui->messageEdit->clear();
    }

    void ChatWindow::onNewMessage(int sender, const QString &username, const QString &content,
                                  bool isImage, const QString &timestamp)
    {
        if(sender == client->getAccount()) return;

        if(isImage) {
            appendImageMessage(username, content, timestamp, false);
        } else {
            appendMessage(username, content, timestamp, false);
        }
    }

    void ChatWindow::onUserOnline(int account, const QString &username)
    {
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
        if (target != currentTargetAccount) return;

        ui->chatView->clear();
        appendSystemMessage(target == 0 ? "—— 群聊历史 ——" : "—— 私聊历史 ——");

        const int self = client->getAccount();

        for (const QJsonValue &val : messages) {
            QJsonObject obj = val.toObject();
            int sender = obj["sender"].toInt();
            QString uname = obj["username"].toString();
            QString content = obj["content"].toString();
            bool isImage = obj["isImage"].toBool();
            QString timestamp = obj["timestamp"].toString();

            bool isSelf = (sender == self);
            if (isImage) {
                appendImageMessage(isSelf ? "You" : uname, content, timestamp, isSelf);
            } else {
                appendMessage(isSelf ? "You" : uname, content, timestamp, isSelf);
            }
        }
    }

    void ChatWindow::onDisconnected()
    {
        QMessageBox::critical(this, "Disconnected", "You have been disconnected from the server");
        close();
    }

    void ChatWindow::appendImageMessage(const QString &username, const QString &base64, const QString &timestamp, bool isSelf)
    {
        QString nameColor = isSelf ? "blue" : "green";
        QString align = isSelf ? "right" : "left";

        // 头部信息（用户名和时间）
        QString header = QString("<div style='text-align:%1;'>"
                                 "<span style='color:%2;font-weight:bold;'>%3</span> "
                                 "<span style='color:gray;font-size:small;'>[%4]</span>"
                                 "</div>")
                             .arg(align).arg(nameColor).arg(username).arg(timestamp);

        // 图片HTML（添加点击事件）
        QString imgHtml = QString("<div style='text-align:%1;'>"
                                  "<a href='image://%2' style='text-decoration:none;'>"
                                  "<img src='data:image/png;base64,%2' style='max-width:200px;cursor:pointer;'/>"
                                  "</a>"
                                  "</div>")
                              .arg(align).arg(base64);

        ui->chatView->append(header);
        ui->chatView->append(imgHtml);
        ui->chatView->append("<br/>");

        // 确保滚动到最新消息
        QTextCursor cursor = ui->chatView->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->chatView->setTextCursor(cursor);
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
        dlg.exec();
    }

    void ChatWindow::showImageDialog(const QString &base64)
    {
        QByteArray imageData = QByteArray::fromBase64(base64.toUtf8());
        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        if (!pixmap.isNull()) {
            QDialog *dialog = new QDialog(this);
            dialog->setWindowTitle("查看图片");
            dialog->resize(600, 400);

            QLabel *label = new QLabel(dialog);
            label->setPixmap(pixmap.scaled(dialog->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            label->setAlignment(Qt::AlignCenter);

            QVBoxLayout *layout = new QVBoxLayout(dialog);
            layout->addWidget(label);
            dialog->setLayout(layout);

            dialog->exec();
        }
    }
