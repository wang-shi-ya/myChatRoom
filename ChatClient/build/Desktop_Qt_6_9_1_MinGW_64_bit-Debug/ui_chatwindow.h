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
    QHBoxLayout *horizontalLayout;
    QListWidget *onlineList;
    QVBoxLayout *leftLayout;
    QVBoxLayout *verticalLayout;
    QTextBrowser *chatView;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *messageEdit;
    QPushButton *sendButton;
    QPushButton *editProfileButton;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(800, 600);
        horizontalLayout = new QHBoxLayout(ChatWindow);
        horizontalLayout->setObjectName("horizontalLayout");
        onlineList = new QListWidget(ChatWindow);
        onlineList->setObjectName("onlineList");
        onlineList->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(onlineList);

        leftLayout = new QVBoxLayout();
        leftLayout->setObjectName("leftLayout");

        horizontalLayout->addLayout(leftLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        chatView = new QTextBrowser(ChatWindow);
        chatView->setObjectName("chatView");
        chatView->setOpenExternalLinks(true);

        verticalLayout->addWidget(chatView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        messageEdit = new QTextEdit(ChatWindow);
        messageEdit->setObjectName("messageEdit");

        horizontalLayout_2->addWidget(messageEdit);

        sendButton = new QPushButton(ChatWindow);
        sendButton->setObjectName("sendButton");

        horizontalLayout_2->addWidget(sendButton);

        editProfileButton = new QPushButton(ChatWindow);
        editProfileButton->setObjectName("editProfileButton");

        horizontalLayout_2->addWidget(editProfileButton);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "chatroom", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "\345\217\221\351\200\201", nullptr));
        editProfileButton->setText(QCoreApplication::translate("ChatWindow", "\344\277\256\346\224\271\350\265\204\346\226\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
