#include "user.h"

User::User(UserType userType, const QString & login, const QString & password, const QDate & date, std::optional<int> licenseKey)
    : m_UserType(userType)
    , m_Login(login)
    , m_Password(password)
    , m_RegisterDate(date)
    , m_LicenseKey(licenseKey)
{

}

UserType User::GetUserType() const
{
    return m_UserType;
}

const QString & User::GetLogin() const
{
    return m_Login;
}

const QString & User::GetPassword() const
{
    return m_Password;
}

const QDate & User::GetRegisterDate() const
{
    return m_RegisterDate;
}

std::optional<int> User::GetLicenseKey() const
{
    return m_LicenseKey;
}
