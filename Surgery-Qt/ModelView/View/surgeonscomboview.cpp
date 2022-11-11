#include "surgeonscomboview.h"

SurgeonsComboView::SurgeonsComboView(SurgeonsModel * model, QWidget *parent) : QComboBox(parent)
{
    m_SurgeonsModel = model;

    connect(model, &SurgeonsModel::dataModified, this, &SurgeonsComboView::refreshData);

    refreshData();
}

void SurgeonsComboView::refreshData()
{
    this->clear();

    for (const auto & surgeon : m_SurgeonsModel->GetData())
    {
        this->addItem(surgeon.GetName(), surgeon.GetId());
    }
}
