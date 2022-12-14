#include "statisticswindow.h"
#include "ui_statisticswindow.h"

#include <QDate>
#include <QLabel>
#include <QMessageBox>

#include "ModelView/Model/genderlistmodel.h"
#include "ModelView/Model/operationtitleslistmodel.h"

#include "Source/handledoperation.h"

#include "Dialog/datechoosedialog.h"
#include "Dialog/sequelachoosedialog.h"
#include "Dialog/diagnosischoosedialog.h"

StatisticsWindow::StatisticsWindow(SurgeonsModel * surgeonsModel, HandledOperationsModel * handledOperationsModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    m_HandledOperationsModel = handledOperationsModel;

    ui->dateFromEdit->setDate(QDate::currentDate());
    ui->dateToEdit->setDate(QDate::currentDate());

    ui->genderCombo->setModel(new GenderListModel());
    ui->operationTitleCombo->setModel(new OperationTitlesListModel());

    m_SurgeonsCombo = new SurgeonsComboView(surgeonsModel);
    ui->verticalLayout_3->addWidget(m_SurgeonsCombo);

    m_RecoveringDaysSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->horizontalLayout_15->insertWidget(1, m_RecoveringDaysSlider);
    m_RecoveringDaysSlider->setMinimum(0);
    m_RecoveringDaysSlider->setMaximum(100);
    ui->horizontalLayout_15->setStretch(0,0);
    ui->horizontalLayout_15->setStretch(1,1);
    ui->horizontalLayout_15->setStretch(2,0);

    m_PatientAgeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->horizontalLayout_16->insertWidget(1, m_PatientAgeSlider);
    m_PatientAgeSlider->setMinimum(16);
    m_PatientAgeSlider->setMaximum(100);
    ui->horizontalLayout_16->setStretch(0,0);
    ui->horizontalLayout_16->setStretch(1,1);
    ui->horizontalLayout_16->setStretch(2,0);

    connect(m_RecoveringDaysSlider, &RangeSlider::lowerValueChanged,
            ui->recDaysLeftLabel, qOverload<int>(&QLabel::setNum));

    connect(m_RecoveringDaysSlider, &RangeSlider::upperValueChanged,
            ui->recDaysRightLabel, qOverload<int>(&QLabel::setNum));

    connect(m_PatientAgeSlider, &RangeSlider::lowerValueChanged,
           ui->patAgeLeftLabel, qOverload<int>(&QLabel::setNum));

    connect(m_PatientAgeSlider, &RangeSlider::upperValueChanged,
           ui->patAgeRightLabel, qOverload<int>(&QLabel::setNum));

    SetOperationTitleFilterEnabled(ui->operationTitleCheckBox->isChecked());
    SetSurgeonFilterEnabled(ui->surgeonCheckBox->isChecked());
    SetDateFilterEnabled(ui->dateCheckBox->isChecked());
    SetSequlaFilterEnabled(ui->sequelaCheckBox->isChecked());
    SetDiagnosisFilterEnabled(ui->diagnosisCheckBox->isChecked());
    SetPatientGenderFilterEnabled(ui->patientGenderCheckBox->isChecked());
    SetRecoveringDaysFilterEnabled(ui->recoveringDaysCheckBox->isChecked());
    SetPatientAgeFilterEnabled(ui->patientAgeCheckBox->isChecked());
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::on_operationTitleCheckBox_stateChanged(int state)
{
    SetOperationTitleFilterEnabled(state);
}

void StatisticsWindow::on_surgeonCheckBox_stateChanged(int state)
{
    SetSurgeonFilterEnabled(state);
}

void StatisticsWindow::on_dateCheckBox_stateChanged(int state)
{
    SetDateFilterEnabled(state);
}

void StatisticsWindow::on_sequelaCheckBox_stateChanged(int state)
{
    SetSequlaFilterEnabled(state);
}

void StatisticsWindow::on_diagnosisCheckBox_stateChanged(int state)
{
    SetDiagnosisFilterEnabled(state);
}

void StatisticsWindow::on_patientGenderCheckBox_stateChanged(int state)
{
    SetPatientGenderFilterEnabled(state);
}

void StatisticsWindow::on_recoveringDaysCheckBox_stateChanged(int state)
{
    SetRecoveringDaysFilterEnabled(state);
}

void StatisticsWindow::on_patientAgeCheckBox_stateChanged(int state)
{
    SetPatientAgeFilterEnabled(state);
}

void StatisticsWindow::SetOperationTitleFilterEnabled(bool state)
{
    ui->operationTitleCombo->setEnabled(state);
}

void StatisticsWindow::SetSurgeonFilterEnabled(bool state)
{
    m_SurgeonsCombo->setEnabled(state);
}

void StatisticsWindow::SetDateFilterEnabled(bool state)
{
    ui->labelFromDate->setEnabled(state);
    ui->labelToDate->setEnabled(state);
    ui->dateFromEdit->setEnabled(state);
    ui->dateToEdit->setEnabled(state);
    ui->openCalendarFromDate->setEnabled(state);
    ui->openCalendarToDate->setEnabled(state);
}

void StatisticsWindow::SetSequlaFilterEnabled(bool state)
{
    ui->sequelaLabel->setEnabled(state);
    ui->sequelaOpenButton->setEnabled(state);
}

void StatisticsWindow::SetDiagnosisFilterEnabled(bool state)
{
    ui->labelDiagnosis->setEnabled(state);
    ui->diagnosisOpenButton->setEnabled(state);
}

void StatisticsWindow::SetPatientGenderFilterEnabled(bool state)
{
    ui->genderCombo->setEnabled(state);
}

void StatisticsWindow::SetRecoveringDaysFilterEnabled(bool state)
{
    ui->recDaysLeftLabel->setEnabled(state);
    ui->recDaysRightLabel->setEnabled(state);
    m_RecoveringDaysSlider->setEnabled(state);
}

void StatisticsWindow::SetPatientAgeFilterEnabled(bool state)
{
    ui->patAgeLeftLabel->setEnabled(state);
    ui->patAgeRightLabel->setEnabled(state);
    m_PatientAgeSlider->setEnabled(state);
}

void StatisticsWindow::on_openCalendarFromDate_clicked()
{
    DateChooseDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto date = dlg.GetDate();

        if (date)
        {
            if (date.value() > ui->dateToEdit->date())
            {
                QMessageBox::warning(this, "Предупреждение", "Время 'С' не может быть больше времени 'По'", QMessageBox::Ok);
                return;
            }

            ui->dateFromEdit->setDate(date.value());
        }
    }
}

void StatisticsWindow::on_openCalendarToDate_clicked()
{
    DateChooseDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto date = dlg.GetDate();

        if (date)
        {
            if (date.value() < ui->dateFromEdit->date())
            {
                QMessageBox::warning(this, "Предупреждение", "Время 'По' не может быть меньше времени 'С'", QMessageBox::Ok);
                return;
            }

            ui->dateToEdit->setDate(date.value());
        }
    }
}

void StatisticsWindow::on_findHandledOperations_clicked()
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

    if (ui->diagnosisCheckBox->isChecked())
    {
        if (!m_Diagnosis)
        {
            QMessageBox::warning(this,"Предупреждение", "Диагноз не выбран", QMessageBox::Ok);
            return;
        }
    }

    std::vector<filterType> filters;

    // go through all checkbox and set up filters
    if (ui->operationTitleCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return operation.m_Operation.GetId() == this->ui->operationTitleCombo->currentData().toInt();
        });
    }

    if (ui->surgeonCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return operation.m_Surgeon.GetId() == this->m_SurgeonsCombo->currentData().toInt();
        });
    }

    if (ui->dateCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return operation.m_Date >= this->ui->dateFromEdit->date() &&
                   operation.m_Date <= this->ui->dateToEdit->date();
        });
    }

    if (ui->patientGenderCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return static_cast<int>(operation.m_PatientGender.GetGenderEnum()) ==
                   this->ui->genderCombo->currentData().toInt();
        });
    }

    if (ui->recoveringDaysCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return operation.m_RecoveringDays >= this->ui->recDaysLeftLabel->text().toInt() &&
                   operation.m_RecoveringDays <= this->ui->recDaysRightLabel->text().toInt();
        });
    }


    if (ui->patientAgeCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            int age = QDate::currentDate().year() - operation.m_PatientDateBirth.year();

            return age >= this->ui->patAgeLeftLabel->text().toInt() &&
                   age <= this->ui->patAgeRightLabel->text().toInt();
        });
    }

    if (ui->sequelaCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            if (!operation.m_Sequela)
                return false;

            return m_Sequela.value().GetId() == operation.m_Sequela.value().GetId();
        });
    }

    if (ui->diagnosisCheckBox->isChecked())
    {
        filters.emplace_back([this](const Hernia::HandledOperation & operation)
        {
            return m_Diagnosis.value().GetType().ToInt() == operation.m_Diagnosis.GetType().ToInt() &&
                    m_Diagnosis.value().GetSize().ToInt() == operation.m_Diagnosis.GetSize().ToInt();
        });
    }

    int filteredOperationCount = GetOperationsByFilters(filters);

    switch(filteredOperationCount)
    {
    case 1:
        ui->label_4->setText("операция");
        break;
    case 2:
    case 3:
    case 4:
        ui->label_4->setText("операции");
        break;
    default:
        ui->label_4->setText("операций");
        break;
    }

    ui->operationsAmountLabel->setNum(filteredOperationCount);
}

int StatisticsWindow::GetOperationsByFilters(const std::vector<filterType> & filters)
{
    int filteredOperationsCounter = 0;

    for (const auto & operation : m_HandledOperationsModel->GetData())
    {
        bool addState = true;

        std::for_each(filters.begin(), filters.end(), [&addState, &operation](const auto & filter)
        {
            if (!filter(operation))
                addState = false;
        });

        if (addState)
        {
            ++filteredOperationsCounter;
        }
    }

    return filteredOperationsCounter;
}

void StatisticsWindow::on_sequelaOpenButton_clicked()
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

void StatisticsWindow::on_diagnosisOpenButton_clicked()
{
    DiagnosisChooseDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto diagnosis = dlg.GetDiagnosis();

        if (diagnosis)
        {
            m_Diagnosis = diagnosis.value();
            ui->labelDiagnosis->setText(diagnosis.value().ToString());
        }
    }
}
