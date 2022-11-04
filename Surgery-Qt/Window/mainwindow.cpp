#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>

#include "Window/statisticswindow.h"
#include "Window/surgeonswindow.h"
#include "Db/databasemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Surgeons = new std::vector<Hernia::Surgeon>;
    db::DatabaseManager::GetInstance().LoadSurgeons(*m_Surgeons);

    m_HandledOperations = new std::vector<Hernia::HandledOperation>;
    db::DatabaseManager::GetInstance().LoadHandledOperations(*m_HandledOperations);

    ui->tabWidget->addTab(new StatisticsWindow(), QString("Статистика"));
    ui->tabWidget->addTab(new OperationsWindow(m_HandledOperations), QString("Операции"));
    ui->tabWidget->addTab(new SurgeonsWindow(m_Surgeons), QString("Хирурги"));
    ui->tabWidget->setTabShape(QTabWidget::Triangular);
}

MainWindow::~MainWindow()
{
    delete ui;
}
