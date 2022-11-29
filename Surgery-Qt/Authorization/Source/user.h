#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

enum class UserType
{
    Admin = 1,
    SimpleUser = 2
};

class User
{
public:
    User(UserType userType, const QString & login, const QString & password, const QDate & date, std::optional<int> licenseKey);

    UserType GetUserType() const;
    const QString & GetLogin() const;
    const QString & GetPassword() const;
    const QDate & GetRegisterDate() const;
    std::optional<int> GetLicenseKey() const;

private:
    UserType m_UserType;
    QString m_Login;
    QString m_Password;
    QDate m_RegisterDate;
    std::optional<int> m_LicenseKey;
};

#endif // USER_H
