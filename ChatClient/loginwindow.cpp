// loginwindow.cpp
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "chatwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    , client(new Client())
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);

    connect(client, &Client::loginSuccess, this, &LoginWindow::onLoginSuccess);
    connect(client, &Client::loginFailed, this, &LoginWindow::onLoginFailed);
    connect(client, &Client::registerSuccess, this, &LoginWindow::onRegisterSuccess);
    connect(client, &Client::registerFailed, this, &LoginWindow::onRegisterFailed);
    connect(client, &Client::connected, this, &LoginWindow::onConnected);
    connect(client, &Client::disconnected, this, &LoginWindow::onDisconnected);

    if (client->connectToServer("127.0.0.1", 12345)) {
        qDebug() << "Successfully connected to server!";
    } else {
        qDebug() << "Failed to connect to server!";
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    bool ok;
    int account = ui->accountEdit->text().toInt(&ok);
    if(!ok || account <= 0) {
        showError("Invalid account number");
        return;
    }
    QString password = ui->passwordEdit->text();
    if(password.isEmpty()) {
        showError("Password cannot be empty");
        return;
    }
    client->login(account, password);
}

void LoginWindow::onRegisterClicked()
{
    bool ok;
    int account = ui->accountEdit->text().toInt(&ok);
    if(!ok || account <= 0) {
        showError("Invalid account number");
        return;
    }
    QString username = ui->usernameEdit->text();
    if(username.isEmpty()) {
        showError("Username cannot be empty");
        return;
    }
    QString password = ui->passwordEdit->text();
    if(password.isEmpty()) {
        showError("Password cannot be empty");
        return;
    }
    client->registerUser(account, username, password);
}

void LoginWindow::onLoginSuccess(int /*account*/, const QString &/*username*/)
{
    ChatWindow *chatWindow = new ChatWindow(client);
    chatWindow->show();
    this->hide();
}

void LoginWindow::onLoginFailed(const QString &error)
{
    showError(error);
}

void LoginWindow::onRegisterSuccess()
{
    QMessageBox::information(this, "Success", "Registration successful!");
}

void LoginWindow::onRegisterFailed(const QString &error)
{
    showError(error);
}

void LoginWindow::onConnected()
{
    ui->statusLabel->setText("Connected to server");
}

void LoginWindow::onDisconnected()
{
    ui->statusLabel->setText("Disconnected from server");
}

void LoginWindow::showError(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}
