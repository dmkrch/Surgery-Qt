#include "operationswindow.h"
#include "ui_operationswindow.h"

#include <QMessageBox>
#include "Db/databasemanager.h"
#include "Dialog/operationadddialog.h"
#include "ModelView/Model/handledoperationsmodel.h"
#include "ModelView/View/handledoperationstableview.h"

OperationsWindow::OperationsWindow(SurgeonsModel * model, HandledOperationsModel * handledOperationsModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsWindow)
{
    ui->setupUi(this);

    m_SurgeonsModel = model;
    m_HandledOperationsModel = handledOperationsModel;
    ui->verticalLayout->addWidget(new HandledOperationsTableView(m_HandledOperationsModel));
}

OperationsWindow::~OperationsWindow()
{
    delete ui;
}

void OperationsWindow::on_addOperationButton_clicked()
{
    OperationAddDialog dlg(m_SurgeonsModel, this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto handledOperation = dlg.GetHandledOperation();

        if (handledOperation)
        {
            // everything is correct. First we try to add to db. If success - add to model as well
            if (db::DatabaseManager::GetInstance().AddHandledOperation(handledOperation.value()))
            {
                int opId = db::DatabaseManager::GetInstance().GetLastAddedHandledOperationId();
                handledOperation.value().m_Id = opId;
                m_HandledOperationsModel->AddHandledOperation(handledOperation.value());

                QMessageBox::information(this,"Успех", "Операция #" + QString::number(handledOperation.value().m_Id) + " успешно добавлена", QMessageBox::Ok);
            }
            else
            {
                QMessageBox::warning(this,"Предупреждение", "Не удалось добавить в базу операцию.", QMessageBox::Ok);
            }
        }
    }
}
