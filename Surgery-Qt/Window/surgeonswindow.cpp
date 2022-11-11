#include "surgeonswindow.h"
#include "ui_surgeonswindow.h"

#include "ModelView/View/surgeonstableview.h"
#include "Dialog/surgeonadddialog.h"
#include "Db/databasemanager.h"
#include <QMessageBox>
#include <QBoxLayout>
#include <QPushButton>

SurgeonsWindow::SurgeonsWindow(SurgeonsModel * model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SurgeonsWindow)
{
    m_SurgeonsModel = model;

    // setting view - qtablewidget
    auto tableView = new SurgeonsTableView(model);
    auto addSurgeonButton = new QPushButton("Добавить хирурга");

    auto vertLayout = new QVBoxLayout;
    vertLayout->addWidget(tableView);
    vertLayout->addWidget(addSurgeonButton);

    this->setLayout(vertLayout);

    connect(addSurgeonButton, &QPushButton::clicked, this, &SurgeonsWindow::on_addSurgeonButton_clicked);
}

SurgeonsWindow::~SurgeonsWindow()
{
    delete ui;
}

void SurgeonsWindow::on_addSurgeonButton_clicked()
{
    SurgeonAddDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        auto surgeon = dlg.GetSurgeon();

        if (surgeon)
        {
            // everything is correct. First we try to add to db. If success - add to model as well
            if (db::DatabaseManager::GetInstance().AddSurgeon(surgeon.value()))
            {
                int surgId = db::DatabaseManager::GetInstance().GetLastAddedSurgeonId();
                surgeon.value().SetId(surgId);
                m_SurgeonsModel->AddSurgeon(surgeon.value());

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
