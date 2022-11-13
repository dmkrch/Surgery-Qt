#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <vector>

#include "Source/surgeon.h"
#include "Source/operation.h"
#include "Source/sequelatype.h"
#include "Source/gender.h"
#include "Source/sequela.h"
#include "Source/operation.h"
#include "Source/handledoperation.h"


namespace db
{
    class DatabaseManager
    {
    private:
        DatabaseManager();

    public:
        static DatabaseManager& GetInstance()
        {
            static DatabaseManager instance;
            return instance;
        }

        void LoadSurgeons(std::vector<Hernia::Surgeon>& surgeons);
        void LoadOperations(std::vector<Hernia::Operation>& operations);
        void LoadSequelaTypes(std::vector<Hernia::SequelaType>& sequelaTypes);
        void LoadSequelas(std::vector<Hernia::Sequela>& sequelas);
        void LoadGenders(std::vector<Hernia::Gender>& genders);
        void LoadHandledOperations(std::vector<Hernia::HandledOperation>& handledOperations);

        bool AddSurgeon(const Hernia::Surgeon & surgeon);
        bool AddHandledOperation(const Hernia::HandledOperation & operation);

        bool DeleteHandledOperation(int operationId);

        int GetLastAddedSurgeonId() const;
        int GetLastAddedHandledOperationId() const;
        std::optional<Hernia::Surgeon> GetSurgeonById(int id);
        std::optional<Hernia::Operation> GetOperationById(int id);
        std::optional<Hernia::Sequela> GetSequelaById(int id);
        bool IsHandledOperationByIdExists(int id);

    private:
        QSqlDatabase m_Db;
    };
}
#endif // DATABASEMANAGER_H
