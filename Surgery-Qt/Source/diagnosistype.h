#ifndef DIAGNOSISTYPE_H
#define DIAGNOSISTYPE_H

#include <QString>

namespace Hernia
{
    enum class DiagnosisTypeEnum
    {
        Inguinal = 1,
        Primary = 2,
        PostOperative = 3,
        Undefined = 10
    };

    class DiagnosisType
    {
    public:
        DiagnosisType();
        explicit DiagnosisType(DiagnosisTypeEnum diagnosisTypeEnum);

        QString ToString() const;
        int ToInt() const;

    private:
        DiagnosisTypeEnum m_DiagnosisType;
    };
}

#endif // DIAGNOSISTYPE_H
