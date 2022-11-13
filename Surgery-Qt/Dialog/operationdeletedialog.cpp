#include "operationdeletedialog.h"
#include "ui_operationdeletedialog.h"

#include <QMessageBox>
#include <QValidator>

OperationDeleteDialog::OperationDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationDeleteDialog)
{
    ui->setupUi(this);

    ui->operationIdEdit->setValidator(new QIntValidator(1, 99999, this));
}

OperationDeleteDialog::~OperationDeleteDialog()
{
    delete ui;
}

int OperationDeleteDialog::GetOperationId() const
{
    return ui->operationIdEdit->text().toInt();
}

void OperationDeleteDialog::on_buttonDelete_clicked()
{
    if (ui->operationIdEdit->text().isEmpty())
    {
         QMessageBox::warning(this,"Предупреждение", "Номер операции не может быть пустым", QMessageBox::Ok);
         return;
    }
    if (ui->operationIdEdit->text().size() > 5)
    {
        QMessageBox::warning(this,"Предупреждение", "Номер операции не может превышать 5 символов", QMessageBox::Ok);
        return;
    }

    // everything is fine, return from dialog
    accept();
}

void OperationDeleteDialog::on_buttonCancel_clicked()
{
    reject();
}
