#ifndef HANDLEDOPERATIONSTABLEVIEW_H
#define HANDLEDOPERATIONSTABLEVIEW_H

#include <QWidget>
#include <QTableWidget>

#include "ModelView/Model/handledoperationsmodel.h"

class HandledOperationsTableView : public QTableWidget
{
    Q_OBJECT
public:
    HandledOperationsTableView(HandledOperationsModel * model, QWidget *parent = nullptr);

public slots:
    void refreshData();

private:
    HandledOperationsModel * m_HandledOperationsModel;
};

#endif // HANDLEDOPERATIONSTABLEVIEW_H
