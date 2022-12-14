#include "databasemanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QSqlError>

namespace db
{
    DatabaseManager::DatabaseManager()
    {
        QString dbPath = QDir::currentPath() + "/../Surgery-Qt/Db/surgery.db";

        m_Db = QSqlDatabase::addDatabase("QSQLITE");
        m_Db.setDatabaseName(dbPath);

        if (!m_Db.open())
            qDebug() << "Error: connection with database fail";
        else
            qDebug() << "Database: connected";
    }

    void DatabaseManager::LoadSurgeons(std::vector<Hernia::Surgeon>& surgeons)
    {
        surgeons.clear();

        QSqlQuery query;
        if (!query.exec("SELECT id, name, gender FROM Surgeon"))
        {
            qDebug() << "error with loading surgeons: " << query.lastError();
            return;
        }

        while(query.next())
        {
            surgeons.emplace_back(query.value(0).toInt(), query.value(1).toString(),
                Hernia::Gender(static_cast<Hernia::GenderEnum>(query.value(2).toInt())));
        }

        // sort vector by name
        std::sort(surgeons.begin(), surgeons.end(),
            [](const Hernia::Surgeon& surg1, const Hernia::Surgeon& surg2)
        {
            return surg1.GetName() < surg2.GetName();
        });
    }

    void DatabaseManager::LoadOperations(std::vector<Hernia::Operation>& operations)
    {
        operations.clear();

        QSqlQuery query;
        if (!query.exec("SELECT id, title FROM Operation"))
        {
            qDebug() << "error with loading operations: " << query.lastError();
            return;
        }

        while(query.next())
        {
            operations.emplace_back(query.value(0).toInt(), query.value(1).toString());
        }

        std::sort(operations.begin(), operations.end(),
            [](const Hernia::Operation& op1, const Hernia::Operation& op2)
        {
            return op1.GetOperationTitle() < op2.GetOperationTitle();
        });
    }

    void DatabaseManager::LoadSequelaTypes(std::vector<Hernia::SequelaType>& sequelaTypes)
    {
        sequelaTypes.clear();

        QSqlQuery query;
        if(!query.exec("SELECT id FROM SequelaType"))
        {
            qDebug() << "error with loading sequela types: " << query.lastError();
            return;
        }

        while(query.next())
        {
            sequelaTypes.emplace_back(static_cast<Hernia::SequelaTypeEnum>(query.value(0).toInt()));
        }
    }

    void DatabaseManager::LoadSequelas(std::vector<Hernia::Sequela>& sequelas)
    {
        sequelas.clear();

        QSqlQuery query;
        if (!query.exec("SELECT id, title, sequela_type FROM Sequela"))
        {
            qDebug() << "error with loading sequelas: " << query.lastError();
            return;
        }

        while(query.next())
        {
            sequelas.emplace_back(query.value(0).toInt(), query.value(1).toString(),
                Hernia::SequelaType(static_cast<Hernia::SequelaTypeEnum>(query.value(2).toInt())));
        }
    }

    void DatabaseManager::LoadGenders(std::vector<Hernia::Gender>& genders)
    {
        genders.clear();

        QSqlQuery query;
        if (!query.exec("SELECT id FROM Gender"))
        {
            qDebug() << "error with loading genders: " << query.lastError();
            return;
        }

        while(query.next())
        {
            genders.emplace_back(static_cast<Hernia::GenderEnum>(query.value(0).toInt()));
        }
    }

    void DatabaseManager::LoadHandledOperations(std::vector<Hernia::HandledOperation>& handledOperations)
    {
        handledOperations.clear();

        QSqlQuery query;
        if (!query.exec("SELECT id, operation, surgeon, handle_date, sequela, patient_gender, recovering_days, \
            patient_birth_date, diagnosis_type, diagnosis_hernia_size FROM HandledOperation"))
        {
            qDebug() << "error with loading handled operations: " << query.lastError();
            return;
        }

        while(query.next())
        {
            int handledOperationId = query.value(0).toInt();
            int operationId = query.value(1).toInt();
            int surgeonId = query.value(2).toInt();
            QDate date = query.value(3).toDate();
            int sequelaId = query.value(4).toInt();
            int patientGender = query.value(5).toInt();
            int recoveringDays = query.value(6).toInt();
            QDate patientBirthDate = query.value(7).toDate();
            int diagnosisTypeId = query.value(8).toInt();
            int diagnosisSizeId = query.value(9).toInt();

            auto operation = GetOperationById(operationId);
            auto surgeon = GetSurgeonById(surgeonId);
            auto gender = Hernia::Gender(static_cast<Hernia::GenderEnum>(patientGender));
            auto sequela = GetSequelaById(sequelaId);

            if (!surgeon || !operation)
                return;

            Hernia::Diagnosis diagnosis = Hernia::Diagnosis(Hernia::DiagnosisType(static_cast<Hernia::DiagnosisTypeEnum>(diagnosisTypeId)),
                                          Hernia::DiagnosisHerniaSize(static_cast<Hernia::DiagnosisHerniaSizeEnum>(diagnosisSizeId)));

            handledOperations.emplace_back(handledOperationId, operation.value(), surgeon.value(), date, sequela, diagnosis,
                gender, patientBirthDate, recoveringDays);
        }
    }

    void DatabaseManager::LoadDiagnosisTypes(std::vector<Hernia::DiagnosisType> & diagnosisTypes)
    {
        diagnosisTypes.clear();

        QSqlQuery query;
        if(!query.exec("SELECT id FROM DiagnosisType"))
        {
            qDebug() << "error with loading diagnosis types: " << query.lastError();
            return;
        }

        while(query.next())
        {
            diagnosisTypes.emplace_back(static_cast<Hernia::DiagnosisTypeEnum>(query.value(0).toInt()));
        }
    }

    bool DatabaseManager::AddSurgeon(const Hernia::Surgeon & surgeon)
    {
        QSqlQuery query;

        query.prepare("INSERT INTO Surgeon(name, gender) VALUES(:surgName, :surgGender); ");
        query.bindValue(":surgName", surgeon.GetName());
        query.bindValue(":surgGender", static_cast<int>(surgeon.GetGender().GetGenderEnum()));

        return query.exec();
    }

    bool DatabaseManager::AddHandledOperation(const Hernia::HandledOperation & operation)
    {
        QSqlQuery query;

        query.prepare("INSERT INTO HandledOperation(operation, surgeon, handle_date, sequela, "
                      "patient_gender, recovering_days, patient_birth_date, diagnosis_type, diagnosis_hernia_size) "
                      "VALUES(:operationId, :surgeonId,"
                      ":date, :sequelaId, :patientGenderId, :recoveringDays, :patientBirthDate, :diagnosis_type, :diagnosis_hernia_size); ");

        query.bindValue(":operationId", operation.m_Operation.GetId());
        query.bindValue(":surgeonId", operation.m_Surgeon.GetId());
        query.bindValue(":date", operation.m_Date);

        if (operation.m_Sequela)
            query.bindValue(":sequelaId", operation.m_Sequela.value().GetId());
        else
            query.bindValue(":sequelaId", QVariant());

        query.bindValue(":patientGenderId", static_cast<int>(operation.m_PatientGender.GetGenderEnum()));
        query.bindValue(":recoveringDays", operation.m_RecoveringDays);
        query.bindValue(":patientBirthDate", operation.m_PatientDateBirth);
        query.bindValue(":diagnosis_type", operation.m_Diagnosis.GetType().ToInt());
        query.bindValue(":diagnosis_hernia_size", operation.m_Diagnosis.GetSize().ToInt());

        return query.exec();
    }

    bool DatabaseManager::DeleteHandledOperation(int operationId)
    {
        if (IsHandledOperationByIdExists(operationId))
        {
            QSqlQuery query;

            query.prepare("delete from HandledOperation where id=:operationId");
            query.bindValue(":operationId", operationId);

            return query.exec();
        }
    }

    int DatabaseManager::GetLastAddedSurgeonId() const
    {
        QSqlQuery query;

        if (!query.exec("SELECT seq FROM sqlite_sequence WHERE name = 'Surgeon'"))
        {
            qDebug() << "error with loading last surgeon id: " << query.lastError();
            return 0;
        }

        query.next();

        return query.value(0).toInt();
    }

    int DatabaseManager::GetLastAddedHandledOperationId() const
    {
        QSqlQuery query;

        if (!query.exec("SELECT seq FROM sqlite_sequence WHERE name = 'HandledOperation'"))
        {
            qDebug() << "error with loading last handled operation id: " << query.lastError();
            return 0;
        }

        query.next();

        return query.value(0).toInt();
    }

    std::optional<Hernia::Surgeon> DatabaseManager::GetSurgeonById(int id)
    {
        std::vector<Hernia::Surgeon> surgeons;
        LoadSurgeons(surgeons);

        auto it = std::find_if(surgeons.begin(), surgeons.end(), [id](const auto & surg)
        {
            return surg.GetId() == id;
        });

        if (it != surgeons.end())
            return *it;
        else
            return std::nullopt;
    }

    std::optional<Hernia::Operation> DatabaseManager::GetOperationById(int id)
    {
        std::vector<Hernia::Operation> operations;
        LoadOperations(operations);

        auto it = std::find_if(operations.begin(), operations.end(), [id](const auto & operation)
        {
            return operation.GetId() == id;
        });

        if (it != operations.end())
            return *it;
        else
            return std::nullopt;
    }

    std::optional<Hernia::Sequela> DatabaseManager::GetSequelaById(int id)
    {
        std::vector<Hernia::Sequela> sequelas;
        LoadSequelas(sequelas);

        auto it = std::find_if(sequelas.begin(), sequelas.end(), [id](const auto & sequela)
        {
            return sequela.GetId() == id;
        });

        if (it != sequelas.end())
            return *it;
        else
            return std::nullopt;
    }

    bool DatabaseManager::IsHandledOperationByIdExists(int id)
    {
        std::vector<Hernia::HandledOperation> handledOperations;
        LoadHandledOperations(handledOperations);

        auto it = std::find_if(handledOperations.begin(), handledOperations.end(), [id](const auto & operation)
        {
            return operation.m_Id == id;
        });

        return it != handledOperations.end();
    }

    std::optional<User> DatabaseManager::GetUserByLogin(const QString & login)
    {
        QSqlQuery query;
        query.prepare("SELECT count(login) from User WHERE login = '" + login + "';");

        if (query.exec())
        {
            query.next();
            if (query.value(0).toInt() > 0)
            {
                query.clear();
                query.prepare("select password, login, user_type, register_date, license_key, id from User WHERE login = '" +
                              login + "';");

                if (!query.exec())
                    return std::nullopt;

                query.next();

                QString password = query.value(0).toString();
                QString login = query.value(1).toString();
                UserType userType = static_cast<UserType>(query.value(2).toInt());
                QDate date = query.value(3).toDate();

                int licenseKey = query.value(4).toInt();
                std::optional<int> licenseKeyOpt;
                if (licenseKey)
                    licenseKeyOpt = licenseKey;

                int id = query.value(5).toInt();

                return User(userType, login, password, date, licenseKeyOpt, id);
                // user is found
            }
        }

        return std::nullopt;
    }

    bool DatabaseManager::AddUser(const User & user)
    {
        QSqlQuery query;

        query.prepare("INSERT INTO User(password, login, license_key, user_type, register_date) "
                      "VALUES(:password, :login, :license_key, :user_type, :register_date); ");

        query.bindValue(":password", user.GetPassword());
        query.bindValue(":login", user.GetLogin());
        query.bindValue(":license_key", QVariant());
        query.bindValue(":user_type", static_cast<int>(user.GetUserType()));
        query.bindValue(":register_date", user.GetRegisterDate());

        return query.exec();
    }

    bool DatabaseManager::CreateLicenseKey()
    {
        QSqlQuery query;

        query.prepare("INSERT INTO LicenseKey DEFAULT VALUES");

        return query.exec();
    }

    int DatabaseManager::GetLastCreatedLicenseKey() const
    {
        QSqlQuery query;

        if (!query.exec("SELECT seq FROM sqlite_sequence WHERE name = 'LicenseKey'"))
        {
            qDebug() << "error with loading last license key id: " << query.lastError();
            return 0;
        }

        query.next();

        return query.value(0).toInt();
    }

    bool DatabaseManager::AddLicenseKeyToUser(int userId, int key)
    {
        QSqlQuery query;

        query.prepare("UPDATE User SET license_key = :key WHERE id = :id;");

        query.bindValue(":key", key);
        query.bindValue(":id", userId);

        return query.exec();
    }
}
