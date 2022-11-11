#include "sequelachoosedialog.h"
#include "ui_sequelachoosedialog.h"

#include <QMessageBox>
#include "Db/databasemanager.h"

SequelaChooseDialog::SequelaChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SequelaChooseDialog)
{
    ui->setupUi(this);

    std::vector<Hernia::SequelaType> sequelaTypes;
    std::vector<Hernia::Sequela> sequelas;

    db::DatabaseManager::GetInstance().LoadSequelaTypes(sequelaTypes);
    db::DatabaseManager::GetInstance().LoadSequelas(sequelas);

    m_Sequelas = sequelas;
    m_SequelaTypes = sequelaTypes;

    for (const auto & seqType : sequelaTypes)
    {
        ui->sequelaTypeCombo->addItem(seqType.ToString(), seqType.ToInt());
    }
}

std::optional<Hernia::Sequela> SequelaChooseDialog::GetSequela() const
{
    return m_Sequela;
}

SequelaChooseDialog::~SequelaChooseDialog()
{
    delete ui;
}

void SequelaChooseDialog::on_selectSequela_clicked()
{
    // checks for correctness
    int sequelaId = ui->sequelaCombo->currentData().toInt();

    if (sequelaId)
    {
        m_Sequela = db::DatabaseManager::GetInstance().GetSequelaById(sequelaId);
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Не выбрано осложнение", QMessageBox::Ok);
    }
}

void SequelaChooseDialog::on_Cancel_clicked()
{
    reject();
}

void SequelaChooseDialog::on_sequelaTypeCombo_currentIndexChanged(int index)
{
    ui->sequelaCombo->clear();

    int seqTypeId = ui->sequelaTypeCombo->currentData().toInt();

    std::for_each(m_Sequelas.begin(), m_Sequelas.end(), [seqTypeId, this](const auto & sequela)
    {
        if (sequela.GetSeqType().ToInt() == seqTypeId)
            ui->sequelaCombo->addItem(sequela.GetTitle(), sequela.GetId());
    });
}
