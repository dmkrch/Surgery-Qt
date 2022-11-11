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
        HandledOperation(int id, Operation operation, Surgeon surgeon,
                         QDate date, std::optional<Sequela> sequela, Gender patientGender,
                         QDate patientBirthDate, int recoveringDays);

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
