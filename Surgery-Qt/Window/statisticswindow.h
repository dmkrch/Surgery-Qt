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
    Q_OBJECT

public:
    StatisticsWindow(SurgeonsModel * model, HandledOperationsModel * handledOperationsModel, QWidget *parent = nullptr);
    ~StatisticsWindow();

private:
    Ui::StatisticsWindow *ui;
    SurgeonsComboView * m_SurgeonsCombo;
    RangeSlider* m_RecoveringDaysSlider;
    RangeSlider* m_PatientAgeSlider;
};

#endif // STATISTICSWINDOW_H
