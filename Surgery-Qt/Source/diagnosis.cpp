#include "diagnosis.h"

namespace Hernia
{
    Diagnosis::Diagnosis()
    {

    }

    Diagnosis::Diagnosis(Hernia::DiagnosisType type, Hernia::DiagnosisHerniaSizeParam size, Hernia::DiagnosisLMFParam lmf,
                         Hernia::DiagnosisPRParam pr, Hernia::DiagnosisWParam w)
    {
        m_DiagnosisType = type;
        m_HerniaSize = size;
        m_W = w;
        m_LMF = lmf;
        m_PR = pr;
    }

    QString Diagnosis::ToString() const
    {
        return m_DiagnosisType.ToString() + " " + m_HerniaSize.ToString() + " " + m_W.ToString() + " " + m_PR.ToString() + " " + m_LMF.ToString();
    }

    DiagnosisType Diagnosis::GetType() const
    {
        return m_DiagnosisType;
    }

    DiagnosisHerniaSizeParam Diagnosis::GetSize() const
    {
        return m_HerniaSize;
    }

    DiagnosisWParam Diagnosis::GetW() const
    {
        return m_W;
    }

    DiagnosisLMFParam Diagnosis::GetLMF() const
    {
        return m_LMF;
    }

    DiagnosisPRParam Diagnosis::GetPR() const
    {
        return m_PR;
    }
}
