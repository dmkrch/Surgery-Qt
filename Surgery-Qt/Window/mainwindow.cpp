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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInfoAccordingToUser(const User &user)
{
    // set window title
    QString userInfo;

    userInfo += "Login: " + user.GetLogin();
    userInfo += "    Access: ";

    userInfo += user.GetLicenseKey() ? "лицензия" : "пробный период";
    userInfo += "    Role: ";

    switch(user.GetUserType())
    {
    case UserType::SimpleUser:
        userInfo += "пользователь";
        break;
    case UserType::Admin:
        userInfo += "администратор";
        break;
    default:
        userInfo += "- ";
        break;
    }

    setWindowTitle(userInfo);

    // now set tabs
    auto surgModel = new SurgeonsModel();
    auto handledOpModel = new HandledOperationsModel();

    ui->tabWidget->addTab(new StatisticsWindow(surgModel, handledOpModel), QString("Статистика"));
    ui->tabWidget->addTab(new OperationsWindow(surgModel, handledOpModel, user.GetUserType()), QString("Операции"));
    ui->tabWidget->addTab(new SurgeonsWindow(surgModel, user.GetUserType()), QString("Хирурги"));
    ui->tabWidget->setTabShape(QTabWidget::Triangular);
}
