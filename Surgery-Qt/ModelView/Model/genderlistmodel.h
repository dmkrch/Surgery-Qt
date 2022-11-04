#ifndef GENDERLISTMODEL_H
#define GENDERLISTMODEL_H

#include <QAbstractListModel>
#include <Source/gender.h>

class GenderListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GenderListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<Hernia::Gender> m_Genders;
};

#endif // GENDERLISTMODEL_H
