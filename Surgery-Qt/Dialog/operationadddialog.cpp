#include "operationadddialog.h"
#include "ui_operationadddialog.h"
#include "ModelView/Model/genderlistmodel.h"
#include "ModelView/Model/operationtitleslistmodel.h"
#include "ModelView/Model/surgeonlistmodel.h"
#include "Dialog/datechoosedialog.h"
#include "Dialog/sequelachoosedialog.h"
#include "Source/sequela.h"

OperationAddDialog::OperationAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationAddDialog)
{
    ui->setupUi(this);

    ui->sequelaCheckBox->setChecked(false);
    SetSequelaItemsEnabled(ui->sequelaCheckBox->isChecked());

    ui->dateEdit->setDate(QDate::currentDate());

    ui->genderCombo->setModel(new GenderListModel());
    ui->operationTitleCombo->setModel(new OperationTitlesListModel());
    ui->surgeonCombo->setModel(new SurgeonListModel());
}

OperationAddDialog::~OperationAddDialog()
{
    delete ui;
}

void OperationAddDialog::SetSequelaItemsEnabled(bool state)
{
    ui->sequelaLabel->setEnabled(state);
    ui->sequelaOpenButton->setEnabled(state);
}

void OperationAddDialog::on_sequelaCheckBox_stateChanged(int state)
{
    SetSequelaItemsEnabled(state);
}

void OperationAddDialog::on_patientAgeSlider_valueChanged(int value)
{
    ui->patientAgeValue->setText(QString::number(value));
}

void OperationAddDialog::on_recoveringDaysSlider_valueChanged(int value)
{
    ui->recoveringDaysValue->setText(QString::number(value));
}

void OperationAddDialog::on_sequelaOpenButton_clicked()
{
    SequelaChooseDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
    {
        auto sequela = dlg.GetSequela();

        if (sequela)
        {
            ui->sequelaLabel->setText(sequela.value().ToString());
        }
    }
}

void OperationAddDialog::on_openCalendarButton_clicked()
{
    DateChooseDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
    {
        auto date = dlg.GetDate();

        if (date)
        {
            ui->dateEdit->setDate(date.value());
        }
    }
}
