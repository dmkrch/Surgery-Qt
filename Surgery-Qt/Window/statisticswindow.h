#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>

#include "ModelView/Model/surgeonsmodel.h"
#include "ModelView/Model/handledoperationsmodel.h"
#include "ModelView/View/surgeonscomboview.h"
#include "Source/CustomWidgets/rangeslider.h"

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QWidget
{
    using filterType = std::function<bool(Hernia::HandledOperation)>;

    Q_OBJECT

public:
    StatisticsWindow(SurgeonsModel * model, HandledOperationsModel * handledOperationsModel, QWidget *parent = nullptr);
    ~StatisticsWindow();

private slots:
    void on_operationTitleCheckBox_stateChanged(int state);
    void on_surgeonCheckBox_stateChanged(int state);
    void on_dateCheckBox_stateChanged(int state);
    void on_sequelaCheckBox_stateChanged(int state);
    void on_diagnosisCheckBox_stateChanged(int state);
    void on_patientGenderCheckBox_stateChanged(int state);
    void on_recoveringDaysCheckBox_stateChanged(int state);
    void on_patientAgeCheckBox_stateChanged(int arg1);
    void on_openCalendarFromDate_clicked();
    void on_openCalendarToDate_clicked();
    void on_findHandledOperations_clicked();

    void on_sequelaOpenButton_clicked();

    void on_diagnosisOpenButton_clicked();

private:
    void SetOperationTitleFilterEnabled(bool state);
    void SetSurgeonFilterEnabled(bool state);
    void SetDateFilterEnabled(bool state);
    void SetSequlaFilterEnabled(bool state);
    void SetDiagnosisFilterEnabled(bool state);
    void SetPatientGenderFilterEnabled(bool state);
    void SetRecoveringDaysFilterEnabled(bool state);
    void SetPatientAgeFilterEnabled(bool state);

    int GetOperationsByFilters(const std::vector<filterType> & filters);

private:
    Ui::StatisticsWindow *ui;
    SurgeonsComboView * m_SurgeonsCombo;
    RangeSlider* m_RecoveringDaysSlider;
    RangeSlider* m_PatientAgeSlider;
    std::optional<Hernia::Sequela> m_Sequela;
    std::optional<Hernia::Diagnosis> m_Diagnosis;

    HandledOperationsModel * m_HandledOperationsModel;
};

#endif // STATISTICSWINDOW_H
