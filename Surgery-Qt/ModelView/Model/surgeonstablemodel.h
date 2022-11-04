#ifndef SURGEONSTABLEMODEL_H
#define SURGEONSTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>

#include "Source/surgeon.h"

class SurgeonsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SurgeonsTableModel(std::vector<Hernia::Surgeon> * surgeons);

    // returns amount of rows
    int rowCount(const QModelIndex &parent) const override;

    // returns amount of columns
    int columnCount(const QModelIndex &parent) const override;

    // returns value of element
    QVariant data(const QModelIndex &index, int role) const override;

    // returns value of header element
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addSurgeon(const Hernia::Surgeon & surgeon);

private:
    enum Column
    {
        ID = 0,
        NAME,
        GENDER,
        LAST
    };
    std::vector<Hernia::Surgeon> * m_Surgeons;
};

#endif // SURGEONSTABLEMODEL_H
