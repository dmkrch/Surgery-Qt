#include "handledoperationstableview.h"

#include <QHeaderView>

HandledOperationsTableView::HandledOperationsTableView(HandledOperationsModel * model, QWidget *parent) : QTableWidget(parent)
{
    m_HandledOperationsModel = model;

    connect(model, &HandledOperationsModel::dataModified, this, &HandledOperationsTableView::refreshData);

    refreshData();
}

void HandledOperationsTableView::refreshData()
{
    this->clear();

    const auto handledOperations = m_HandledOperationsModel->GetData();

    this->setColumnCount(9);
    this->setRowCount(handledOperations.size());
    this->setHorizontalHeaderLabels(QStringList() << "#" << "Название" << "Хирург" << "Дата"
                                          << "Диагноз" << "Осложнение" << "Койко-дни" << "Пол пациента" << "Возраст пациента");


    this->horizontalHeader()->setMinimumSectionSize(50);

    for (int row = 0; row < handledOperations.size(); ++row)
    {
        QTableWidgetItem * id = new QTableWidgetItem();
        id->setText(QString::number(handledOperations[row].m_Id));
        this->setItem(row, 0, id);

        QTableWidgetItem * operationTitle = new QTableWidgetItem();
        operationTitle->setText(handledOperations[row].m_Operation.GetOperationTitle());
        this->setItem(row, 1, operationTitle);

        QTableWidgetItem * surgName = new QTableWidgetItem();
        surgName->setText(handledOperations[row].m_Surgeon.GetName());
        this->setItem(row, 2, surgName);

        QTableWidgetItem * date = new QTableWidgetItem();
        date->setText(QString::number(handledOperations[row].m_Date.day()) + "." +
                      QString::number(handledOperations[row].m_Date.month()) + "." +
                      QString::number(handledOperations[row].m_Date.year()));
        this->setItem(row, 3, date);

        QTableWidgetItem * diagnosis = new QTableWidgetItem();
        diagnosis->setText("Отсутствует");
        this->setItem(row, 4, diagnosis);

        QTableWidgetItem * sequela = new QTableWidgetItem();
        if (handledOperations[row].m_Sequela)
        {
            sequela->setText(handledOperations[row].m_Sequela.value().ToString());
        }
        else
        {
            sequela->setText("Отсутствует");
        }
        this->setItem(row, 5, sequela);

        QTableWidgetItem * recDays = new QTableWidgetItem();
        recDays->setText(QString::number(handledOperations[row].m_RecoveringDays));
        this->setItem(row, 6, recDays);

        QTableWidgetItem * patientGender = new QTableWidgetItem();
        patientGender->setText(handledOperations[row].m_PatientGender.ToString());
        this->setItem(row, 7, patientGender);

        QTableWidgetItem * patientAge = new QTableWidgetItem();
        int age = QDate::currentDate().year() - handledOperations[row].m_PatientDateBirth.year();
        patientAge->setText(QString::number(age));
        this->setItem(row, 8, patientAge);
    }
}
