#ifndef AUTHORIZATIONMAINWINDOW_H
#define AUTHORIZATIONMAINWINDOW_H

#include <QWidget>
#include <QDialog>

#include "Authorization/Source/user.h"

namespace Ui {
class AuthorizationMainWindow;
}

class AuthorizationMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationMainWindow(QWidget *parent = nullptr);
    ~AuthorizationMainWindow();

    virtual void closeEvent(QCloseEvent *event) override;
    const User & GetUser() const;

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_licenseButton_clicked();

private:
    Ui::AuthorizationMainWindow *ui;
    User m_CurrentUser;
};

#endif // AUTHORIZATIONMAINWINDOW_H
