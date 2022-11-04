#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Window/operationswindow.h"
#include "Source/surgeon.h"
#include "Source/handledoperation.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<Hernia::Surgeon> * m_Surgeons;
    std::vector<Hernia::HandledOperation> * m_HandledOperations;
};
#endif // MAINWINDOW_H
