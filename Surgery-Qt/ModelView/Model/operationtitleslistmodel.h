#ifndef OPERATIONTITLESLISTMODEL_H
#define OPERATIONTITLESLISTMODEL_H

#include <QAbstractListModel>
#include "Source/operation.h"

class OperationTitlesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit OperationTitlesListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<Hernia::Operation> m_Operations;
};

#endif // OPERATIONTITLESLISTMODEL_H
