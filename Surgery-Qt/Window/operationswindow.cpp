#include "operationswindow.h"
#include "ui_operationswindow.h"
#include "Dialog/operationadddialog.h"

OperationsWindow::OperationsWindow(std::vector<Hernia::HandledOperation> * handledOperations, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsWindow)
{
    m_HandledOperations = handledOperations;
    ui->setupUi(this);
}

OperationsWindow::~OperationsWindow()
{
    delete ui;
}

void OperationsWindow::on_addOperationButton_clicked()
{
    OperationAddDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
    {
//        auto handledOperation = dlg.GetHandledOperation();

//        if (handledOperation)
//        {
//            // everything is correct. First we try to add to db. If success - add to model as well
//            if (db::DatabaseManager::GetInstance().AddHandledOperation(handledOperation.value()))
//            {
//                int opId = db::DatabaseManager::GetInstance().GetLastAddedHandledOperationId();
//                handledOperation.value().SetId(opId);
//                m_HanldedOperationsTableModel->addHandledOperation(handledOperation.value());

//                QMessageBox::information(this,"Успех", "Операция #" + handledOperation.value().GetId() + " успешно добавлена", QMessageBox::Ok);
//            }
//            else
//            {
//                QMessageBox::warning(this,"Предупреждение", "Не удалось добавить в базу операцию.", QMessageBox::Ok);
//            }
//        }
    }
}
