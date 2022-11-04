#include "surgeonswindow.h"
#include "ui_surgeonswindow.h"

#include "Dialog/surgeonadddialog.h"
#include "Db/databasemanager.h"
#include <QMessageBox>

SurgeonsWindow::SurgeonsWindow(std::vector<Hernia::Surgeon> * surgeons, QWidget *parent)
    : QWidget(parent)
    , m_Surgeons(surgeons)
    , ui(new Ui::SurgeonsWindow)
{
    ui->setupUi(this);

    // connections. sender - receiver
    connect(ui->addSurgeonButton, &QPushButton::clicked,
            this, &SurgeonsWindow::OnAddSurgeonButtonClicked);

    m_SurgeonsTableModel = new SurgeonsTableModel(m_Surgeons);
    ui->tableView->setModel(m_SurgeonsTableModel);
}

SurgeonsWindow::~SurgeonsWindow()
{
    delete ui;
}

void SurgeonsWindow::OnAddSurgeonButtonClicked()
{
    SurgeonAddDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
    {
        auto surgeon = dlg.GetSurgeon();

        if (surgeon)
        {
            // everything is correct. First we try to add to db. If success - add to model as well
            if (db::DatabaseManager::GetInstance().AddSurgeon(surgeon.value()))
            {
                int surgId = db::DatabaseManager::GetInstance().GetLastAddedSurgeonId();
                surgeon.value().SetId(surgId);
                m_SurgeonsTableModel->addSurgeon(surgeon.value());

                QMessageBox::information(this,"Успех", "Хирург " + surgeon.value().GetName() + " успешно добавлен", QMessageBox::Ok);
            }
            else
            {
                QMessageBox::warning(this,"Предупреждение", "Не удалось добавить в базу хирируга. \
                    Проверьте уникальность имени", QMessageBox::Ok);
            }
        }
    }
}
