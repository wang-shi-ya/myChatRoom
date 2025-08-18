#include "profiledialog.h"
#include "ui_profiledialog.h"
#include <QMessageBox>

ProfileDialog::ProfileDialog(Client *client, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProfileDialog)
    , client(client)
{
    ui->setupUi(this);
    setWindowTitle("修改资料");

    connect(ui->submitButton, &QPushButton::clicked, this, &ProfileDialog::onSubmitClicked);

    // 绑定 Client 信号
    connect(client, &Client::usernameUpdated, this, &ProfileDialog::onUsernameUpdated);
    connect(client, &Client::usernameUpdateFailed, this, &ProfileDialog::onUsernameUpdateFailed);
    connect(client, &Client::passwordUpdated, this, &ProfileDialog::onPasswordUpdated);
    connect(client, &Client::passwordUpdateFailed, this, &ProfileDialog::onPasswordUpdateFailed);
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

void ProfileDialog::onSubmitClicked()
{
    QString newUsername = ui->usernameEdit->text().trimmed();
    QString oldPassword = ui->oldPasswordEdit->text().trimmed();
    QString newPassword = ui->passwordEdit->text().trimmed();

    if (newUsername.isEmpty() && newPassword.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入新用户名或新密码");
        return;
    }

    if (!newUsername.isEmpty()) {
        client->updateUsername(newUsername);
    }

    if (!newPassword.isEmpty()) {
        if (oldPassword.isEmpty()) {
            QMessageBox::warning(this, "提示", "修改密码时必须输入原密码");
            return;
        }
        client->updatePassword(oldPassword, newPassword); // ⬅ 传原密码 + 新密码
    }
}


void ProfileDialog::onUsernameUpdated(const QString &newUsername)
{
    QMessageBox::information(this, "成功", "用户名已修改为：" + newUsername);
}

void ProfileDialog::onUsernameUpdateFailed()
{
    QMessageBox::critical(this, "失败", "修改用户名失败");
}

void ProfileDialog::onPasswordUpdated()
{
    QMessageBox::information(this, "成功", "密码已修改");
}

void ProfileDialog::onPasswordUpdateFailed()
{
    QMessageBox::critical(this, "失败", "修改密码失败");
}
