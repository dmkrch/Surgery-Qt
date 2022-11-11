#ifndef SURGEONSCOMBOVIEW_H
#define SURGEONSCOMBOVIEW_H

#include <QWidget>
#include <QComboBox>

#include "ModelView/Model/surgeonsmodel.h"

class SurgeonsComboView : public QComboBox
{
    Q_OBJECT
public:
    SurgeonsComboView(SurgeonsModel * model, QWidget *parent = nullptr);

public slots:
    void refreshData();

private:
    SurgeonsModel * m_SurgeonsModel;
};

#endif // SURGEONSCOMBOVIEW_H
