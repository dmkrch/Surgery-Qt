#include "diagnosis.h"

namespace Hernia
{
    Diagnosis::Diagnosis()
        : m_DiagnosisType(Hernia::DiagnosisTypeEnum::Undefined)
        , m_HerniaSize(Hernia::DiagnosisHerniaSizeEnum::Undefined)
    {

    }

    Diagnosis::Diagnosis(Hernia::DiagnosisType type, Hernia::DiagnosisHerniaSize size)
        : m_DiagnosisType(type)
        , m_HerniaSize(size)
    {

    }

    QString Diagnosis::ToString() const
    {
        return m_DiagnosisType.ToString() + " " + m_HerniaSize.ToString();
    }

    DiagnosisType Diagnosis::GetType() const
    {
        return m_DiagnosisType;
    }

    DiagnosisHerniaSize Diagnosis::GetSize() const
    {
        return m_HerniaSize;
    }

    DiagnosisHerniaSize::DiagnosisHerniaSize()
        : m_HerniaSize(Hernia::DiagnosisHerniaSizeEnum::Undefined)
    {

    }

    DiagnosisHerniaSize::DiagnosisHerniaSize(DiagnosisHerniaSizeEnum size)
        : m_HerniaSize(size)
    {

    }

    QString DiagnosisHerniaSize::ToString() const
    {
        switch(m_HerniaSize)
        {
        case DiagnosisHerniaSizeEnum::s1:
            return "S1";
            break;
        case DiagnosisHerniaSizeEnum::s2:
            return "S2";
            break;
        case DiagnosisHerniaSizeEnum::s3:
            return "S3";
            break;
        case DiagnosisHerniaSizeEnum::s4:
            return "S4";
            break;
        case DiagnosisHerniaSizeEnum::s5:
            return "S5";
            break;
        default:
            return "-";
            break;
        }
    }

    int DiagnosisHerniaSize::ToInt() const
    {
        return static_cast<int>(m_HerniaSize);
    }
}
