#include "surgeonsmodel.h"

#include "Db/databasemanager.h"

SurgeonsModel::SurgeonsModel()
{
    db::DatabaseManager::GetInstance().LoadSurgeons(m_Surgeons);
}

const std::vector<Hernia::Surgeon> & SurgeonsModel::GetData() const
{
    return m_Surgeons;
}

void SurgeonsModel::AddSurgeon(const Hernia::Surgeon & surgeon)
{
    m_Surgeons.push_back(surgeon);
    emit dataModified();
}
