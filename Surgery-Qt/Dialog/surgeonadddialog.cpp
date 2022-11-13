#include "surgeonadddialog.h"
#include "ui_surgeonadddialog.h"
#include "Source/gender.h"
#include "Db/databasemanager.h"
#include "ModelView/Model/genderlistmodel.h"
#include <QMessageBox>
#include <QDebug>

SurgeonAddDialog::SurgeonAddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SurgeonAddDialog)
{
    ui->setupUi(this);

    // connections. sender - receiver
    connect(ui->buttonAdd, &QPushButton::clicked,
            this, &SurgeonAddDialog::OnAddButtonClicked);

    connect(ui->buttonCancel, &QPushButton::clicked,
            this, &SurgeonAddDialog::OnCancelButtonClicked);

    m_GendersListModel = new GenderListModel();
    ui->genderCombobox->setModel(m_GendersListModel);
}

SurgeonAddDialog::~SurgeonAddDialog()
{
    delete ui;
}

void SurgeonAddDialog::OnCancelButtonClicked()
{
    // closes the dialog and returns QDialog::Reject()
    reject();
}

void SurgeonAddDialog::OnAddButtonClicked()
{
    QString surgeonName = ui->surgeonNameEdit->text();

    if (surgeonName.isEmpty())
    {
        QMessageBox::warning(this,"Предупреждение", "Имя не может быть пустым", QMessageBox::Ok);
    }
    else if (surgeonName.length() > 50)
    {
         QMessageBox::warning(this,"Предупреждение", "Имя не может превышать 30 символов", QMessageBox::Ok);
    }
    else
    {
        int genderValue = ui->genderCombobox->currentData().toInt();

        m_SurgeonToAdd = Hernia::Surgeon(0, surgeonName, Hernia::Gender(Hernia::GenderEnum(genderValue)));

        // closes the dialog and returns QDialog::Accept()
        accept();
    }
}

std::optional<Hernia::Surgeon> SurgeonAddDialog::GetSurgeon() const
{
    return m_SurgeonToAdd;
}
