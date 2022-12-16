#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <QString>

namespace Hernia
{
    template <typename T>
    class DiagnosisParameter
    {
    public:
        DiagnosisParameter() = default;

        DiagnosisParameter(T param)
        {
            m_Param = param;
        }

        virtual ~DiagnosisParameter() = default;

        virtual QString ToString() const = 0;

        virtual int ToInt() const
        {
            return static_cast<int>(m_Param);
        }

    protected:
        T m_Param;
    };

    // Definitions of different Param-classes of Diagnosis

    enum class DiagnosisHerniaSizeEnum
    {
        s1 = 1,
        s2 = 2,
        s3 = 3,
        s4 = 4,
        s5 = 5,
        Undefined = 10
    };

    class DiagnosisHerniaSizeParam : public DiagnosisParameter<DiagnosisHerniaSizeEnum>
    {
    public:
        using BaseType = DiagnosisParameter<DiagnosisHerniaSizeEnum>;
        using BaseType::BaseType;

        virtual QString ToString() const override
        {
            switch(BaseType::m_Param)
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
    };

    enum class DiagnosisTypeEnum
    {
        Inguinal = 1,
        Primary = 2,
        PostOperative = 3,
        Undefined = 10
    };

    class DiagnosisType : public DiagnosisParameter<DiagnosisTypeEnum>
    {
    public:
        using BaseType = DiagnosisParameter<DiagnosisTypeEnum>;
        using BaseType::BaseType;

        virtual QString ToString() const override
        {
            switch(BaseType::m_Param)
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
    };

    enum class DiagnosisPREnum
    {
        P = 1,
        R = 2,
        Undefined = 10
    };

    class DiagnosisPRParam : public DiagnosisParameter<DiagnosisPREnum>
    {
    public:
        using BaseType = DiagnosisParameter<DiagnosisPREnum>;
        using BaseType::BaseType;

        virtual QString ToString() const override
        {
            switch(BaseType::m_Param)
            {
            case DiagnosisPREnum::P:
                return "P";
            case DiagnosisPREnum::R:
                return "R";
            default:
                return "Не определено";
            }
        }
    };

    enum class DiagnosisLMFEnum
    {
        L = 1,
        M = 2,
        F = 3,
        Undefined = 10
    };

    class DiagnosisLMFParam : public DiagnosisParameter<DiagnosisLMFEnum>
    {
    public:
        using BaseType = DiagnosisParameter<DiagnosisLMFEnum>;
        using BaseType::BaseType;

        virtual QString ToString() const override
        {
            switch(BaseType::m_Param)
            {
            case DiagnosisLMFEnum::L:
                return "L";
            case DiagnosisLMFEnum::M:
                return "M";
            case DiagnosisLMFEnum::F:
                return "F";
            default:
                return "Не определено";
            }
        }
    };

    enum class DiagnosisWEnum
    {
        W1 = 1,
        W2 = 2,
        W3 = 3,
        Undefined = 10
    };

    class DiagnosisWParam : public DiagnosisParameter<DiagnosisWEnum>
    {
    public:
        using BaseType = DiagnosisParameter<DiagnosisWEnum>;
        using BaseType::BaseType;

        virtual QString ToString() const override
        {
            switch(BaseType::m_Param)
            {
            case DiagnosisWEnum::W1:
                return "W1";
            case DiagnosisWEnum::W2:
                return "W2";
            case DiagnosisWEnum::W3:
                return "W3";
            default:
                return "Не определено";
            }
        }
    };

    class Diagnosis
    {
    public:
        Diagnosis();
        Diagnosis(Hernia::DiagnosisType type, Hernia::DiagnosisHerniaSizeParam size, Hernia::DiagnosisLMFParam lmf,
                  Hernia::DiagnosisPRParam pr, Hernia::DiagnosisWParam w);

        QString ToString() const;

        Hernia::DiagnosisType GetType() const;
        Hernia::DiagnosisHerniaSizeParam GetSize() const;
        Hernia::DiagnosisWParam GetW() const;
        Hernia::DiagnosisLMFParam GetLMF() const;
        Hernia::DiagnosisPRParam GetPR() const;

    private:
        Hernia::DiagnosisType m_DiagnosisType;
        Hernia::DiagnosisHerniaSizeParam m_HerniaSize;
        Hernia::DiagnosisWParam m_W;
        Hernia::DiagnosisLMFParam m_LMF;
        Hernia::DiagnosisPRParam m_PR;
    };
}

#endif // DIAGNOSIS_H
