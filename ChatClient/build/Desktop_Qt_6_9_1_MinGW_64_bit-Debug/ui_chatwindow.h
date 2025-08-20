/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QListWidget *onlineList;
    QPushButton *sendButton;
    QTextEdit *messageEdit;
    QPushButton *editProfileButton;
    QPushButton *sendImageButton;
    QWidget *widget;
    QVBoxLayout *leftLayout;
    QTextBrowser *chatView;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(800, 600);
        onlineList = new QListWidget(ChatWindow);
        onlineList->setObjectName("onlineList");
        onlineList->setGeometry(QRect(6, 6, 200, 588));
        onlineList->setMaximumSize(QSize(200, 16777215));
        sendButton = new QPushButton(ChatWindow);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(660, 470, 131, 21));
        messageEdit = new QTextEdit(ChatWindow);
        messageEdit->setObjectName("messageEdit");
        messageEdit->setGeometry(QRect(210, 461, 441, 131));
        editProfileButton = new QPushButton(ChatWindow);
        editProfileButton->setObjectName("editProfileButton");
        editProfileButton->setGeometry(QRect(660, 570, 131, 18));
        sendImageButton = new QPushButton(ChatWindow);
        sendImageButton->setObjectName("sendImageButton");
        sendImageButton->setGeometry(QRect(660, 520, 131, 18));
        widget = new QWidget(ChatWindow);
        widget->setObjectName("widget");
        leftLayout = new QVBoxLayout(widget);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(0, 0, 0, 0);
        chatView = new QTextBrowser(ChatWindow);
        chatView->setObjectName("chatView");
        chatView->setGeometry(QRect(210, 10, 581, 441));
        chatView->setOpenExternalLinks(true);
        widget1 = new QWidget(ChatWindow);
        widget1->setObjectName("widget1");
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "chatroom", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "\345\217\221\351\200\201", nullptr));
        editProfileButton->setText(QCoreApplication::translate("ChatWindow", "\344\277\256\346\224\271\350\265\204\346\226\231", nullptr));
        sendImageButton->setText(QCoreApplication::translate("ChatWindow", "\345\217\221\351\200\201\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
