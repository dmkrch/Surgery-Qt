#include "Window/mainwindow.h"

#include <QApplication>
#include "Authorization/Window/authorizationmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;

    AuthorizationMainWindow authorizationWindow;

    if (authorizationWindow.exec() == QDialog::Accepted)
    {
        mainWindow.show();
    }
    else
    {
        return 1;
    }

    return a.exec();
}
