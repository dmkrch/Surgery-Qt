#include "handledoperation.h"

namespace Hernia
{
    HandledOperation::HandledOperation()
        : m_Id(0), m_RecoveringDays(-1)
    {

    }

    HandledOperation::HandledOperation(int id, const Operation & operation, const Surgeon & surgeon,
                     const QDate & date, std::optional<Sequela> sequela, const Diagnosis & diagnosis, const Gender & patientGender,
                     const QDate & patientBirthDate, int recoveringDays)
    {
        m_Id = id;
        m_Operation = operation;
        m_Surgeon = surgeon;
        m_Date = date;
        m_Sequela = sequela;
        m_Diagnosis = diagnosis;
        m_PatientGender = patientGender;
        m_PatientDateBirth = patientBirthDate;
        m_RecoveringDays = recoveringDays;
    }
}
