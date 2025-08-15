#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(Client *client, QWidget *parent = nullptr);
    ~ProfileDialog();

private slots:
    void onSubmitClicked();
    void onUsernameUpdated(const QString &newUsername);
    void onUsernameUpdateFailed();
    void onPasswordUpdated();
    void onPasswordUpdateFailed();

private:
    Ui::ProfileDialog *ui;
    Client *client;
};

#endif // PROFILEDIALOG_H
