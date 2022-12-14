#include "operationadddialog.h"
#include "ui_operationadddialog.h"
#include <QMessageBox>
#include "ModelView/Model/genderlistmodel.h"
#include "ModelView/Model/operationtitleslistmodel.h"
#include "Dialog/datechoosedialog.h"
#include "Dialog/sequelachoosedialog.h"
#include "Dialog/diagnosischoosedialog.h"
#include "Db/databasemanager.h"
#include "Source/sequela.h"
#include "Source/handledoperation.h"
#include "Source/diagnosis.h"

OperationAddDialog::OperationAddDialog(SurgeonsModel * model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationAddDialog)
{
    ui->setupUi(this);

    ui->sequelaCheckBox->setChecked(false);
    SetSequelaItemsEnabled(ui->sequelaCheckBox->isChecked());

    ui->dateEdit->setDate(QDate::currentDate());

    ui->genderCombo->setModel(new GenderListModel());
    ui->operationTitleCombo->setModel(new OperationTitlesListModel());

    m_SurgeonsCombo = new SurgeonsComboView(model);
    ui->verticalLayout_3->addWidget(m_SurgeonsCombo);
}

OperationAddDialog::~OperationAddDialog()
{
    delete ui;
}

std::optional<Hernia::HandledOperation> OperationAddDialog::GetHandledOperation() const
{
    return m_HandledOperation;
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

    if (dlg.exec() == QDialog::Accepted)
    {
        auto sequela = dlg.GetSequela();

        if (sequela)
        {
            m_Sequela = sequela.value();
            ui->sequelaLabel->setText(sequela.value().ToString());
        }
    }
}

void OperationAddDialog::on_openCalendarButton_clicked()
{
    DateChooseDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto date = dlg.GetDate();

        if (date)
        {
            ui->dateEdit->setDate(date.value());
        }
    }
}

void OperationAddDialog::on_addOperationButton_clicked()
{
    // validations
    if (ui->sequelaCheckBox->isChecked())
    {
        if (!m_Sequela)
        {
            QMessageBox::warning(this,"Предупреждение", "Осложнение не выбрано", QMessageBox::Ok);
            return;
        }
    }

    if (!m_Diagnosis)
    {
        QMessageBox::warning(this,"Предупреждение", "Диагноз не выбран", QMessageBox::Ok);
        return;
    }

    auto operation = db::DatabaseManager::GetInstance().GetOperationById(ui->operationTitleCombo->currentData().toInt());

    if (!operation)
    {
        QMessageBox::warning(this,"Предупреждение", "Название операции не выбрано", QMessageBox::Ok);
        return;
    }

    auto surgeon = db::DatabaseManager::GetInstance().GetSurgeonById(m_SurgeonsCombo->currentData().toInt());

    if (!surgeon)
    {
        QMessageBox::warning(this, "Предупреждение", "Врач не выбран", QMessageBox::Ok);
        return;
    }

    auto date = ui->dateEdit->date();
    int genderInt = ui->genderCombo->currentData().toInt();
    auto gender = Hernia::Gender(static_cast<Hernia::GenderEnum>(genderInt));
    QDate birthDate = QDate::currentDate().addYears(-ui->patientAgeSlider->value());
    int recoveringDays = ui->recoveringDaysSlider->value();

    // if checkbox disabled - we set sequela to null
    if (!ui->sequelaCheckBox->isChecked())
        m_Sequela = std::nullopt;

    m_HandledOperation = Hernia::HandledOperation(0, operation.value(), surgeon.value(), date, m_Sequela, m_Diagnosis.value(),
                                                  gender, birthDate, recoveringDays);

    accept();
}

void OperationAddDialog::on_pushButton_2_clicked()
{
    DiagnosisChooseDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto diagnosis = dlg.GetDiagnosis();

        if (diagnosis)
        {
            m_Diagnosis = diagnosis.value();
            ui->diagnosisLabel->setText(diagnosis.value().ToString());
        }
    }
}
