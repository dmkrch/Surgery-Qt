#ifndef OPERATIONADDDIALOG_H
#define OPERATIONADDDIALOG_H

#include <QDialog>
#include "Source/sequela.h"

namespace Ui {
class OperationAddDialog;
}

class OperationAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OperationAddDialog(QWidget *parent = nullptr);
    ~OperationAddDialog();

private slots:
    void on_sequelaCheckBox_stateChanged(int arg1);
    void on_patientAgeSlider_valueChanged(int value);
    void on_recoveringDaysSlider_valueChanged(int value);

    void on_sequelaOpenButton_clicked();

    void on_openCalendarButton_clicked();

private:
    void SetSequelaItemsEnabled(bool state);

private:
    Ui::OperationAddDialog *ui;
    std::optional<Hernia::Sequela> m_Sequela;
};

#endif // OPERATIONADDDIALOG_H
