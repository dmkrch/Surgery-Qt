#ifndef SURGEONSMODEL_H
#define SURGEONSMODEL_H

#include "QObject"

#include "Source/surgeon.h"

class SurgeonsModel : public QObject
{
    Q_OBJECT

public:
    SurgeonsModel();

    void AddSurgeon(const Hernia::Surgeon & surgeon);

    const std::vector<Hernia::Surgeon> & GetData() const;

signals:
    void dataModified();

private:
    std::vector<Hernia::Surgeon> m_Surgeons;
};

#endif // SURGEONSMODEL_H
