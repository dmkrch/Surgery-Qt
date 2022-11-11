#ifndef OPERATIONADDDIALOG_H
#define OPERATIONADDDIALOG_H

#include <QDialog>
#include "Source/sequela.h"
#include "Source/handledoperation.h"
#include "ModelView/View/surgeonscomboview.h"
#include "ModelView/Model/surgeonsmodel.h"

namespace Ui {
class OperationAddDialog;
}

class OperationAddDialog : public QDialog
{
    Q_OBJECT

public:
    OperationAddDialog(SurgeonsModel * model, QWidget *parent = nullptr);
    ~OperationAddDialog();

    std::optional<Hernia::HandledOperation> GetHandledOperation() const;

private slots:
    void on_sequelaCheckBox_stateChanged(int arg1);
    void on_patientAgeSlider_valueChanged(int value);
    void on_recoveringDaysSlider_valueChanged(int value);
    void on_sequelaOpenButton_clicked();
    void on_openCalendarButton_clicked();
    void on_addOperationButton_clicked();

private:
    void SetSequelaItemsEnabled(bool state);

private:
    Ui::OperationAddDialog *ui;
    std::optional<Hernia::Sequela> m_Sequela;
    std::optional<Hernia::HandledOperation> m_HandledOperation;
    SurgeonsComboView * m_SurgeonsCombo;
};

#endif // OPERATIONADDDIALOG_H
