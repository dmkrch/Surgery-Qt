#include "sequelachoosedialog.h"
#include "ui_sequelachoosedialog.h"

SequelaChooseDialog::SequelaChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SequelaChooseDialog)
{
    ui->setupUi(this);
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
    accept();
}

void SequelaChooseDialog::on_Cancel_clicked()
{
    reject();
}

void SequelaChooseDialog::on_sequelaTypeCombo_currentIndexChanged(int index)
{

}
