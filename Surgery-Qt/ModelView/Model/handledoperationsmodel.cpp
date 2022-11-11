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
