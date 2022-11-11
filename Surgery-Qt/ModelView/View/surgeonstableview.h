#ifndef SURGEONSTABLEVIEW_H
#define SURGEONSTABLEVIEW_H

#include <QWidget>
#include <QTableWidget>

#include "ModelView/Model/surgeonsmodel.h"

class SurgeonsTableView : public QTableWidget
{
    Q_OBJECT
public:
    SurgeonsTableView(SurgeonsModel * model, QWidget *parent = nullptr);

public slots:
    void refreshData();

private:
    SurgeonsModel * m_SurgeonsModel;
};

#endif // SURGEONSTABLEVIEW_H
