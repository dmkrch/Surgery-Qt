#include "statisticswindow.h"
#include "ui_statisticswindow.h"

#include <QDate>

#include "ModelView/Model/genderlistmodel.h"
#include "ModelView/Model/operationtitleslistmodel.h"

StatisticsWindow::StatisticsWindow(SurgeonsModel * surgeonsModel, HandledOperationsModel * handledOperationsModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    ui->genderCombo->setModel(new GenderListModel());
    ui->operationTitleCombo->setModel(new OperationTitlesListModel());

    m_SurgeonsCombo = new SurgeonsComboView(surgeonsModel);
    ui->verticalLayout_3->addWidget(m_SurgeonsCombo);


    m_RecoveringDaysSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->verticalLayout_6->addWidget(m_RecoveringDaysSlider);
    m_RecoveringDaysSlider->setMinimum(0);
    m_RecoveringDaysSlider->setMaximum(100);

    m_PatientAgeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->verticalLayout_8->addWidget(m_PatientAgeSlider);
    m_PatientAgeSlider->setMinimum(16);
    m_PatientAgeSlider->setMaximum(100);
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}
