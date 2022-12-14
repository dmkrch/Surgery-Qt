#include "diagnosistype.h"

namespace Hernia
{
    DiagnosisType::DiagnosisType()
        : m_DiagnosisType(DiagnosisTypeEnum::Undefined)
    {

    }

    DiagnosisType::DiagnosisType(DiagnosisTypeEnum diagnosisTypeEnum)
    {
        m_DiagnosisType = diagnosisTypeEnum;
    }

    QString DiagnosisType::ToString() const
    {
        switch(m_DiagnosisType)
        {
        case DiagnosisTypeEnum::Inguinal:
            return "Паховая грыжа";
        case DiagnosisTypeEnum::Primary:
            return "Первичная грыжа";
        case DiagnosisTypeEnum::PostOperative:
            return "Послеоперационная грыжа";
        default:
            return "Не определено";
        }
    }

    int DiagnosisType::ToInt() const
    {
      return static_cast<int>(m_DiagnosisType);
    }
}
