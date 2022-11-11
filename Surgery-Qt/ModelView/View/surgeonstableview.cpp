#include "surgeonstableview.h"

SurgeonsTableView::SurgeonsTableView(SurgeonsModel * model, QWidget *parent) : QTableWidget(parent)
{
    m_SurgeonsModel = model;

    connect(model, &SurgeonsModel::dataModified, this, &SurgeonsTableView::refreshData);

    refreshData();
}

void SurgeonsTableView::refreshData()
{
    this->clear();

    const auto surgeons = m_SurgeonsModel->GetData();

    this->setRowCount(surgeons.size());
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels(QStringList() << "#" << "Имя" << "Пол");

    for (int row = 0; row < surgeons.size(); ++row)
    {
        QTableWidgetItem * surgId = new QTableWidgetItem();
        surgId->setText(QString::number(surgeons[row].GetId()));
        this->setItem(row, 0, surgId);

        QTableWidgetItem * surgName = new QTableWidgetItem();
        surgName->setText(surgeons[row].GetName());
        this->setItem(row, 1, surgName);

        QTableWidgetItem * surgGender = new QTableWidgetItem();
        surgGender->setText(surgeons[row].GetGender().ToString());
        this->setItem(row, 2, surgGender);
    }
}

