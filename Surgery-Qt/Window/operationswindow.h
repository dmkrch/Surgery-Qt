#ifndef OPERATIONSWINDOW_H
#define OPERATIONSWINDOW_H

#include <QWidget>
#include "Source/handledoperation.h"

namespace Ui {
class OperationsWindow;
}

class OperationsWindow : public QWidget
{
    Q_OBJECT

public:
    OperationsWindow(std::vector<Hernia::HandledOperation> * handledOperations, QWidget *parent = nullptr);
    ~OperationsWindow();

private slots:
    void on_addOperationButton_clicked();

private:
    Ui::OperationsWindow *ui;
    std::vector<Hernia::HandledOperation> * m_HandledOperations;

};

#endif // OPERATIONSWINDOW_H
