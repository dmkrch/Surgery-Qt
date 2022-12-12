#ifndef SURGEONSWINDOW_H
#define SURGEONSWINDOW_H

#include <QWidget>
#include "ModelView/Model/surgeonsmodel.h"
#include "Authorization/Source/user.h"

namespace Ui {
class SurgeonsWindow;
}

class SurgeonsWindow : public QWidget
{
    Q_OBJECT

public:
    SurgeonsWindow(SurgeonsModel * model, UserType userType, QWidget * parent = nullptr);
    ~SurgeonsWindow();

private slots:
    void on_addSurgeonButton_clicked();

private:
    Ui::SurgeonsWindow *ui;
    SurgeonsModel * m_SurgeonsModel;
};

#endif // SURGEONSWINDOW_H
