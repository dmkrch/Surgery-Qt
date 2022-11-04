#include "surgeonstablemodel.h"
#include "Db/databasemanager.h"

SurgeonsTableModel::SurgeonsTableModel(std::vector<Hernia::Surgeon> * surgeons)
{
    if (!surgeons)
        throw ("nullptr surgeons passed");

    m_Surgeons = surgeons;
}

int SurgeonsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_Surgeons->size();
}

int SurgeonsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(LAST);
}

QVariant SurgeonsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_Surgeons->size() <= index.row() || role != Qt::DisplayRole)
        return QVariant();

    auto surgeon = (*m_Surgeons)[index.row()];

    switch (index.column())
    {
    case ID:
        return surgeon.GetId();
    case NAME:
        return surgeon.GetName();
    case GENDER:
        return surgeon.GetGender().ToString();
    default:
        return QString("Не определено");
    }
}

QVariant SurgeonsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical)
        return section;

    switch(section)
    {
    case ID:
        return QString("#");
    case NAME:
        return QString("ФИО");
    case GENDER:
        return QString("Пол");
    default:
        return QString("Не определено");
    }

    return QVariant();
}

void SurgeonsTableModel::addSurgeon(const Hernia::Surgeon & surgeon)
{
    int row = m_Surgeons->size();
    beginInsertRows(QModelIndex(), row, row);
    m_Surgeons->push_back(std::move(surgeon));
    endInsertRows();
}
