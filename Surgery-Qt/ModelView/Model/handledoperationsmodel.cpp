#include "handledoperationsmodel.h"

#include "Db/databasemanager.h"

HandledOperationsModel::HandledOperationsModel()
{
    db::DatabaseManager::GetInstance().LoadHandledOperations(m_HandledOperations);
}

const std::vector<Hernia::HandledOperation> & HandledOperationsModel::GetData() const
{
    return m_HandledOperations;
}

void HandledOperationsModel::AddHandledOperation(const Hernia::HandledOperation & handledOperation)
{
    m_HandledOperations.push_back(handledOperation);
    emit dataModified();
}

void HandledOperationsModel::DeleteHandledOperation(int operationId)
{
    m_HandledOperations.erase(std::remove_if(m_HandledOperations.begin(), m_HandledOperations.end(),
        [operationId](const auto & operation)
    {
        return (operation.m_Id == operationId);
    }), m_HandledOperations.end());

    emit dataModified();
}
