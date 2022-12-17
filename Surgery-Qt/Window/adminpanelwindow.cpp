#include "adminpanelwindow.h"
#include "ui_adminpanelwindow.h"

#include <QMessageBox>
#include "Db/databasemanager.h"

AdminPanelWindow::AdminPanelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanelWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Администрирование");
}

AdminPanelWindow::~AdminPanelWindow()
{
    delete ui;
}

void AdminPanelWindow::on_pushButton_clicked()
{
    QString userLogin = ui->lineEdit->text();

    if (userLogin.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", "Поле не может быть пустым", QMessageBox::Ok);
        return;
    }

    auto user = db::DatabaseManager::GetInstance().GetUserByLogin(userLogin);

    if (!user)
    {
        QMessageBox::warning(this, "Предупреждение", "Пользователя с данным логином не существует", QMessageBox::Ok);
        return;
    }

    if (user.value().GetUserType() == UserType::Admin)
    {
        QMessageBox::warning(this, "Предупреждение", "Пользователь уже является администратором!", QMessageBox::Ok);
        return;
    }

    // everything is correct and we can add his role as admin

    if (db::DatabaseManager::GetInstance().MakeUserToBeAdmin(user.value()))
        QMessageBox::information(this, "Успех", "Пользователю успешно установлена роль администратора", QMessageBox::Ok);
    else
        QMessageBox::warning(this, "Предупреждение", "Не удалось передать роль администратора!", QMessageBox::Ok);
}
