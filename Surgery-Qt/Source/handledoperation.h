#ifndef HANDLEDOPERATION_H
#define HANDLEDOPERATION_H

#include <QDate>

#include "operation.h"
#include "surgeon.h"
#include "sequela.h"
#include "gender.h"

namespace Hernia
{
    class HandledOperation
    {
    public:
        HandledOperation();
        HandledOperation(int id, const Operation & operation, const Surgeon & surgeon,
                         const QDate & date, std::optional<Sequela> sequela, const Gender & patientGender,
                         const QDate & patientBirthDate, int recoveringDays);

        int m_Id;
        Operation m_Operation;
        Surgeon m_Surgeon;
        QDate m_Date;
        std::optional<Sequela> m_Sequela;
        Gender m_PatientGender;
        QDate m_PatientDateBirth;
        int m_RecoveringDays;
    };
}

#endif // HANDLEDOPERATION_H
