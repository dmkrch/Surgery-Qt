#ifndef AUTHORIZATIONMAINWINDOW_H
#define AUTHORIZATIONMAINWINDOW_H

#include <QWidget>
#include <QDialog>

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

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::AuthorizationMainWindow *ui;
};

#endif // AUTHORIZATIONMAINWINDOW_H
