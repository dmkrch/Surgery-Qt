#ifndef OPERATIONSWINDOW_H
#define OPERATIONSWINDOW_H

#include <QWidget>
#include "Source/handledoperation.h"
#include "ModelView/Model/surgeonsmodel.h"
#include "ModelView/Model/handledoperationsmodel.h"

namespace Ui {
class OperationsWindow;
}

class OperationsWindow : public QWidget
{
    Q_OBJECT

public:
    OperationsWindow(SurgeonsModel * model, HandledOperationsModel * handledOperationsModel, QWidget *parent = nullptr);
    ~OperationsWindow();

private slots:
    void on_addOperationButton_clicked();
    void on_deleteOperationButton_clicked();

private:
    Ui::OperationsWindow *ui;
    SurgeonsModel * m_SurgeonsModel;
    HandledOperationsModel * m_HandledOperationsModel;
};

#endif // OPERATIONSWINDOW_H
