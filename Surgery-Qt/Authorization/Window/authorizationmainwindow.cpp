#include "authorizationmainwindow.h"
#include "ui_authorizationmainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>
#include "Db/databasemanager.h"
#include "PaypalPayment/paypaldialog.h"

AuthorizationMainWindow::AuthorizationMainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationMainWindow)
{
    ui->setupUi(this);

    ui->passwordRegisterEdit->setEchoMode(QLineEdit::Password);
    ui->authorizePasswordEdit->setEchoMode(QLineEdit::Password);

    this->setWindowTitle("Хирургия");
}

AuthorizationMainWindow::~AuthorizationMainWindow()
{
    delete ui;
}

void AuthorizationMainWindow::on_loginButton_clicked()
{
    if (ui->authorizeLoginEdit->text().isEmpty() || ui->authorizeLoginEdit->text().length() > 15)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин не может превышать 15 символов или быть пустым!", QMessageBox::Ok);
        return;
    }

    if (ui->authorizePasswordEdit->text().isEmpty() || ui->authorizePasswordEdit->text().length() > 15)
    {
        QMessageBox::warning(this, "Предупреждение", "Пароль не может превышать 15 символов или быть пустым!", QMessageBox::Ok);
        return;
    }

    const QString login = ui->authorizeLoginEdit->text();
    const auto foundedUserByLogin = db::DatabaseManager::GetInstance().GetUserByLogin(login);

    if (!foundedUserByLogin)
    {
        QMessageBox::warning(this, "Предупреждение", "Пользователь с данным логином не существует существует!", QMessageBox::Ok);
        return;
    }

    if (ui->authorizePasswordEdit->text() != foundedUserByLogin.value().GetPassword())
    {
        QMessageBox::warning(this, "Предупреждение", "Неправильный пароль!", QMessageBox::Ok);
        return;
    }

    // if user has no license key - check his register date
    if (!foundedUserByLogin.value().GetLicenseKey())
    {
        auto deltaDays = foundedUserByLogin.value().GetRegisterDate().daysTo(QDate::currentDate());

        if (deltaDays > 3)
        {
            QMessageBox::warning(this, "Предупреждение", "Пробный период пользования программой истек!", QMessageBox::Ok);
            return;
        }
    }

    QMessageBox::information(this, "Успех", "Вы успешно авторизовались!", QMessageBox::Ok);
    m_CurrentUser = foundedUserByLogin.value();
    accept();
}

void AuthorizationMainWindow::on_registerButton_clicked()
{
    // validations on lineEdits
    if (ui->loginRegisterEdit->text().isEmpty() || ui->loginRegisterEdit->text().length() > 15)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин не может превышать 15 символов или быть пустым!", QMessageBox::Ok);
        return;
    }

    if (ui->passwordRegisterEdit->text().isEmpty() || ui->passwordRegisterEdit->text().length() > 15)
    {
        QMessageBox::warning(this, "Предупреждение", "Пароль не может превышать 15 символов или быть пустым!", QMessageBox::Ok);
        return;
    }

    // first we take login from login_form and check from db, if there is such user
    // if not - create it and add to db
    const QString login = ui->loginRegisterEdit->text();
    const auto foundedUserByLogin = db::DatabaseManager::GetInstance().GetUserByLogin(login);

    if (foundedUserByLogin)
    {
        QMessageBox::warning(this, "Предупреждение", "Пользователь с данным логином уже существует!", QMessageBox::Ok);
        return;
    }

    User user(UserType::SimpleUser, login, ui->passwordRegisterEdit->text(), QDate::currentDate(), std::nullopt, 0);

    if (db::DatabaseManager::GetInstance().AddUser(user))
        QMessageBox::information(this, "Успех", "Пользователь " + user.GetLogin() + " успешно заригстрирован!", QMessageBox::Ok);
}

void AuthorizationMainWindow::closeEvent(QCloseEvent *event)
{
    reject();
}

const User &AuthorizationMainWindow::GetUser() const
{
    return m_CurrentUser;
}

void AuthorizationMainWindow::on_licenseButton_clicked()
{
    // validations on lineEdits
    QString userLogin = ui->licenseLoginEdit->text();

    if (userLogin.isEmpty() || userLogin.length() > 15)
    {
        QMessageBox::warning(this, "Предупреждение", "Логин не может превышать 15 символов или быть пустым!", QMessageBox::Ok);
        return;
    }

    auto user = db::DatabaseManager::GetInstance().GetUserByLogin(userLogin);

    if (!user)
    {
        QMessageBox::warning(this, "Предупреждение", "Не существует пользователя с данным логином!", QMessageBox::Ok);
        return;
    }

    if (user.value().GetLicenseKey())
    {
        QMessageBox::warning(this, "Предупреждение", "Пользователь " + userLogin + " уже купил лицензию", QMessageBox::Ok);
        return;
    }

    // now everything is fine, we can proceed the payment via paypal
    PaypalDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        db::DatabaseManager::GetInstance().CreateLicenseKey();
        int key = db::DatabaseManager::GetInstance().GetLastCreatedLicenseKey();
        user.value().SetLicenseKey(key);

        if (db::DatabaseManager::GetInstance().AddLicenseKeyToUser(user.value().GetId(), key))
        {
            QMessageBox::information(this, "Успех", "Лицензия для пользователя " + userLogin + " успешно куплена", QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(this, "Предупреждение", "Не удалось купить лицензию!", QMessageBox::Ok);
        }

    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Не удалось купить лицензию!", QMessageBox::Ok);
    }
}
