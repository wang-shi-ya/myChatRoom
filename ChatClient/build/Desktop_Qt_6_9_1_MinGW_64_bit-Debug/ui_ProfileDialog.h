/********************************************************************************
** Form generated from reading UI file 'ProfileDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEDIALOG_H
#define UI_PROFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProfileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelUsername;
    QLineEdit *usernameEdit;
    QLabel *labelPassword;
    QLineEdit *passwordEdit;
    QPushButton *submitButton;

    void setupUi(QDialog *ProfileDialog)
    {
        if (ProfileDialog->objectName().isEmpty())
            ProfileDialog->setObjectName("ProfileDialog");
        ProfileDialog->resize(300, 200);
        verticalLayout = new QVBoxLayout(ProfileDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelUsername = new QLabel(ProfileDialog);
        labelUsername->setObjectName("labelUsername");

        verticalLayout->addWidget(labelUsername);

        usernameEdit = new QLineEdit(ProfileDialog);
        usernameEdit->setObjectName("usernameEdit");

        verticalLayout->addWidget(usernameEdit);

        labelPassword = new QLabel(ProfileDialog);
        labelPassword->setObjectName("labelPassword");

        verticalLayout->addWidget(labelPassword);

        passwordEdit = new QLineEdit(ProfileDialog);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordEdit);

        submitButton = new QPushButton(ProfileDialog);
        submitButton->setObjectName("submitButton");

        verticalLayout->addWidget(submitButton);


        retranslateUi(ProfileDialog);

        QMetaObject::connectSlotsByName(ProfileDialog);
    } // setupUi

    void retranslateUi(QDialog *ProfileDialog)
    {
        ProfileDialog->setWindowTitle(QCoreApplication::translate("ProfileDialog", "\344\277\256\346\224\271\350\265\204\346\226\231", nullptr));
        labelUsername->setText(QCoreApplication::translate("ProfileDialog", "\346\226\260\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("ProfileDialog", "\350\276\223\345\205\245\346\226\260\347\224\250\346\210\267\345\220\215\357\274\210\345\217\257\351\200\211\357\274\211", nullptr));
        labelPassword->setText(QCoreApplication::translate("ProfileDialog", "\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("ProfileDialog", "\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201\357\274\210\345\217\257\351\200\211\357\274\211", nullptr));
        submitButton->setText(QCoreApplication::translate("ProfileDialog", "\346\217\220\344\272\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileDialog: public Ui_ProfileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEDIALOG_H
