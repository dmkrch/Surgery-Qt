#include "diagnosischoosedialog.h"
#include "ui_diagnosischoosedialog.h"

#include <QMessageBox>
#include "Db/databasemanager.h"

DiagnosisChooseDialog::DiagnosisChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagnosisChooseDialog)
{
    ui->setupUi(this);

    std::vector<Hernia::DiagnosisType> m_DiagnosisTypes;
    m_DiagnosisTypes.emplace_back(Hernia::DiagnosisTypeEnum::Inguinal);
    m_DiagnosisTypes.emplace_back(Hernia::DiagnosisTypeEnum::PostOperative);
    m_DiagnosisTypes.emplace_back(Hernia::DiagnosisTypeEnum::Primary);

    std::vector<Hernia::DiagnosisHerniaSizeParam> m_HerniaSizes;
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s1);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s2);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s3);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s4);
    m_HerniaSizes.emplace_back(Hernia::DiagnosisHerniaSizeEnum::s5);

    std::vector<Hernia::DiagnosisLMFParam> m_DiagnosisLMFs;
    m_DiagnosisLMFs.emplace_back(Hernia::DiagnosisLMFEnum::L);
    m_DiagnosisLMFs.emplace_back(Hernia::DiagnosisLMFEnum::M);
    m_DiagnosisLMFs.emplace_back(Hernia::DiagnosisLMFEnum::F);

    std::vector<Hernia::DiagnosisPRParam> m_DiagnosisPRs;
    m_DiagnosisPRs.emplace_back(Hernia::DiagnosisPREnum::P);
    m_DiagnosisPRs.emplace_back(Hernia::DiagnosisPREnum::R);

    std::vector<Hernia::DiagnosisWParam> m_DiagnosisWs;
    m_DiagnosisWs.emplace_back(Hernia::DiagnosisWEnum::W1);
    m_DiagnosisWs.emplace_back(Hernia::DiagnosisWEnum::W2);
    m_DiagnosisWs.emplace_back(Hernia::DiagnosisWEnum::W3);

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

    // setting combobox for LMF param
    for (const auto & lmf : m_DiagnosisLMFs)
    {
        ui->diagnosisLMFCombo->addItem(lmf.ToString(), lmf.ToInt());
    }

    // setting combobox for PR param
    for (const auto & pr : m_DiagnosisPRs)
    {
        ui->diagnosisPRCombo->addItem(pr.ToString(), pr.ToInt());
    }

    // setting combobox for W param
    for (const auto & w : m_DiagnosisWs)
    {
        ui->diagnosisWCombo->addItem(w.ToString(), w.ToInt());
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
    int lmf = ui->diagnosisLMFCombo->currentData().toInt();
    int pr = ui->diagnosisPRCombo->currentData().toInt();
    int w = ui->diagnosisWCombo->currentData().toInt();

    if (typeId != 0 && sizeId != 0 && lmf != 0 && pr != 0 && w != 0)
    {
        m_CurrentDiagnosis = Hernia::Diagnosis(Hernia::DiagnosisType(static_cast<Hernia::DiagnosisTypeEnum>(typeId)),
                             Hernia::DiagnosisHerniaSizeParam(static_cast<Hernia::DiagnosisHerniaSizeEnum>(sizeId)),
                             Hernia::DiagnosisLMFParam(static_cast<Hernia::DiagnosisLMFEnum>(lmf)),
                             Hernia::DiagnosisPRParam(static_cast<Hernia::DiagnosisPREnum>(pr)),
                             Hernia::DiagnosisWParam(static_cast<Hernia::DiagnosisWEnum>(w)));
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
