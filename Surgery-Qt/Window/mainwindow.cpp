#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>

#include "Db/databasemanager.h"
#include "Window/statisticswindow.h"
#include "Window/surgeonswindow.h"
#include "ModelView/Model/surgeonsmodel.h"
#include "ModelView/Model/handledoperationsmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto surgModel = new SurgeonsModel();
    auto handledOpModel = new HandledOperationsModel();

    ui->tabWidget->addTab(new StatisticsWindow(surgModel, handledOpModel), QString("Статистика"));
    ui->tabWidget->addTab(new OperationsWindow(surgModel, handledOpModel), QString("Операции"));
    ui->tabWidget->addTab(new SurgeonsWindow(surgModel), QString("Хирурги"));
    ui->tabWidget->setTabShape(QTabWidget::Triangular);
}

MainWindow::~MainWindow()
{
    delete ui;
}
