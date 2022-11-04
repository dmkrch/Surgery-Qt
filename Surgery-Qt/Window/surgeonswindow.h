#ifndef SURGEONSWINDOW_H
#define SURGEONSWINDOW_H

#include <QWidget>
#include "ModelView/Model/surgeonstablemodel.h"

namespace Ui {
class SurgeonsWindow;
}

class SurgeonsWindow : public QWidget
{
    Q_OBJECT

public:
    SurgeonsWindow(std::vector<Hernia::Surgeon> * surgeons, QWidget *parent = nullptr);
    ~SurgeonsWindow();

private slots:
    void OnAddSurgeonButtonClicked();

private:
    Ui::SurgeonsWindow *ui;
    SurgeonsTableModel *m_SurgeonsTableModel;
    std::vector<Hernia::Surgeon> * m_Surgeons;
};

#endif // SURGEONSWINDOW_H
