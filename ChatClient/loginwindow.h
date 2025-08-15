// loginwindow.h
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "client.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onLoginSuccess(int account, const QString &username);
    void onLoginFailed(const QString &error);
    void onRegisterSuccess();
    void onRegisterFailed(const QString &error);
    void onConnected();
    void onDisconnected();

private:
    Ui::LoginWindow *ui;
    Client *client;

    void showError(const QString &message);
};

#endif // LOGINWINDOW_H
