#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "diagnosistype.h"

namespace Hernia
{
    enum class DiagnosisHerniaSizeEnum
    {
        s1 = 1,
        s2 = 2,
        s3 = 3,
        s4 = 4,
        s5 = 5,
        Undefined = 10
    };

    class DiagnosisHerniaSize
    {
    public:
        DiagnosisHerniaSize();
        DiagnosisHerniaSize(Hernia::DiagnosisHerniaSizeEnum size);

        QString ToString() const;
        int ToInt() const;

    private:
        Hernia::DiagnosisHerniaSizeEnum m_HerniaSize;
    };

    class Diagnosis
    {
    public:
        Diagnosis();
        Diagnosis(Hernia::DiagnosisType type, Hernia::DiagnosisHerniaSize size);

        QString ToString() const;

        Hernia::DiagnosisType GetType() const;
        Hernia::DiagnosisHerniaSize GetSize() const;

    private:
        Hernia::DiagnosisType m_DiagnosisType;
        Hernia::DiagnosisHerniaSize m_HerniaSize;
    };
}

#endif // DIAGNOSIS_H
