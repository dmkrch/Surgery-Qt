#include "handledoperation.h"

namespace Hernia
{
    HandledOperation::HandledOperation()
        : m_Id(0), m_RecoveringDays(-1)
    {

    }

    HandledOperation::HandledOperation(int id, Operation operation, Surgeon surgeon,
                     QDate date, Sequela sequela, Gender patientGender,
                     QDate patientBirthDate, int recoveringDays)
    {
        m_Id = id;
        m_Operation = operation;
        m_Surgeon = surgeon;
        m_Date = date;
        m_Sequela = sequela;
        m_PatientGender = patientGender;
        m_PatientDateBirth = patientBirthDate;
        m_RecoveringDays = recoveringDays;
    }
}
