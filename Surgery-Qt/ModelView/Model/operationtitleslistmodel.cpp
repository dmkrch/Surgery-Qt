#include "operationtitleslistmodel.h"
#include "Db/databasemanager.h"

OperationTitlesListModel::OperationTitlesListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    db::DatabaseManager::GetInstance().LoadOperations(m_Operations);
}

int OperationTitlesListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Operations.size();
}

QVariant OperationTitlesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (role == Qt::DisplayRole)
    {
         return m_Operations[index.row()].GetOperationTitle();
    }
    else if (role == Qt::UserRole)
    {
        return static_cast<int>(m_Operations[index.row()].GetOperationId());
    }

    return QVariant();
}
