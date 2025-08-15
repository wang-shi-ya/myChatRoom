/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *accountEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *statusLabel;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(LoginWindow);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);

        verticalLayout->addWidget(label);

        accountEdit = new QLineEdit(LoginWindow);
        accountEdit->setObjectName("accountEdit");

        verticalLayout->addWidget(accountEdit);

        usernameEdit = new QLineEdit(LoginWindow);
        usernameEdit->setObjectName("usernameEdit");

        verticalLayout->addWidget(usernameEdit);

        passwordEdit = new QLineEdit(LoginWindow);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        registerButton = new QPushButton(LoginWindow);
        registerButton->setObjectName("registerButton");

        horizontalLayout->addWidget(registerButton);


        verticalLayout->addLayout(horizontalLayout);

        statusLabel = new QLabel(LoginWindow);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);


        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\350\201\212\345\244\251\345\256\244\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "\350\201\212\345\244\251\345\256\244\347\231\273\345\275\225", nullptr));
        accountEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\264\246\345\217\267", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214", nullptr));
        statusLabel->setText(QCoreApplication::translate("LoginWindow", "Status: Not connected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
