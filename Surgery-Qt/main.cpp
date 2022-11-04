#include "Window/mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "Source/gender.h"
#include "Source/surgeon.h"
#include "Source/sequelatype.h"
#include "Db/databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
