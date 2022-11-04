#ifndef SURGEONLISTMODEL_H
#define SURGEONLISTMODEL_H

#include <QAbstractListModel>
#include "Source/surgeon.h"

class SurgeonListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SurgeonListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<Hernia::Surgeon> m_Surgeons;
};

#endif // SURGEONLISTMODEL_H
