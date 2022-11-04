#include "surgeonlistmodel.h"
#include "Db/databasemanager.h"

SurgeonListModel::SurgeonListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    db::DatabaseManager::GetInstance().LoadSurgeons(m_Surgeons);
}

int SurgeonListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Surgeons.size();
}

QVariant SurgeonListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

    if (role == Qt::DisplayRole)
    {
         return m_Surgeons[index.row()].GetName();
    }
    else if (role == Qt::UserRole)
    {
        return static_cast<int>(m_Surgeons[index.row()].GetId());
    }

    return QVariant();
}
