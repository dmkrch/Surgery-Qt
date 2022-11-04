#include "genderlistmodel.h"
#include "Db/databasemanager.h"

GenderListModel::GenderListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    db::DatabaseManager::GetInstance().LoadGenders(m_Genders);
}

int GenderListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_Genders.size();
}

QVariant GenderListModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
        return QVariant();

   if (role == Qt::DisplayRole)
   {
        return m_Genders[index.row()].ToString();
   }
   else if (role == Qt::UserRole)
   {
       return static_cast<int>(m_Genders[index.row()].GetGenderEnum());
   }

   return QVariant();
}
