#include "diagnosischoosedialog.h"
#include "ui_diagnosischoosedialog.h"

#include <QMessageBox>
#include "Db/databasemanager.h"

DiagnosisChooseDialog::DiagnosisChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagnosisChooseDialog)
{
    ui->setupUi(this);

    db::DatabaseManager::GetInstance().LoadDiagnosisTypes(m_DiagnosisTypes);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s1);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s2);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s3);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s4);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s5);

    // setting combobox for types
    for (const auto & diagnosisType : m_DiagnosisTypes)
    {
        ui->diagnosisTypeCombo->addItem(diagnosisType.ToString(), diagnosisType.ToInt());
    }

    // setting combobox for hernia sizes
    for (const auto & size : m_HerniaSizes)
    {
        ui->herniaSizeCombo->addItem(size.ToString(), size.ToInt());
    }
}

DiagnosisChooseDialog::~DiagnosisChooseDialog()
{
    delete ui;
}

std::optional<Hernia::Diagnosis> DiagnosisChooseDialog::GetDiagnosis() const
{
    return m_CurrentDiagnosis;
}

void DiagnosisChooseDialog::on_selectDiagnosis_clicked()
{
    int typeId = ui->diagnosisTypeCombo->currentData().toInt();
    int sizeId = ui->herniaSizeCombo->currentData().toInt();

    if (typeId != 0 && sizeId != 0)
    {
        m_CurrentDiagnosis = Hernia::Diagnosis(Hernia::DiagnosisType(static_cast<Hernia::DiagnosisTypeEnum>(typeId)),
                                Hernia::DiagnosisHerniaSize(static_cast<Hernia::DiagnosisHerniaSizeEnum>(sizeId)));
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Некорректные данные", QMessageBox::Ok);
    }
}

void DiagnosisChooseDialog::on_Cancel_clicked()
{
    reject();
}
