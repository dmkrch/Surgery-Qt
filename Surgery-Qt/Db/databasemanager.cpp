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

//        QSqlQuery query;
//        if (!query.exec("SELECT op_id, op_title_id, surger_id, seq_id, gender_id, patient_age, rec_days, op_date FROM operation"))
//        {
//            qDebug() << "error with loading handled operations: " << query.lastError();
//            return;
//        }

//        while(query.next())
//        {
//            operations.emplace_back(query.value(0).toInt(), // op_id
//                                  query.value(1).toInt(), // op_title_id
//                                  query.value(2).toInt(), // surger_id
//                                  query.value(3).toInt(), // seq_id
//                                  query.value(4).toInt(), // gender_id
//                                  query.value(5).toInt(), // patient_age
//                                  query.value(6).toInt(), // rec_days
//                                  query.value(7).toString()); // op_date
//        }
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
//        QSqlQuery query;

//        query.prepare("INSERT INTO Surgeon(name, gender) VALUES(:surgName, :surgGender); ");
//        query.bindValue(":surgName", surgeon.GetName());
//        query.bindValue(":surgGender", static_cast<int>(surgeon.GetGender().GetGenderEnum()));

//        return query.exec();

        return true;
    }

    int DatabaseManager::GetLastAddedSurgeonId() const
    {
        QSqlQuery query;

        if (!query.exec("SELECT seq FROM sqlite_sequence WHERE name = 'Surgeon'"))
        {
            qDebug() << "error with loading genders: " << query.lastError();
            return -1;
        }

        query.next();

        return query.value(0).toInt();
    }
}
