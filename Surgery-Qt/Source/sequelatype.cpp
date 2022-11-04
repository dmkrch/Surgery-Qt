#include "sequelatype.h"

namespace Hernia
{
    SequelaType::SequelaType()
        : m_SequelaType(SequelaTypeEnum::Undefined)
    {

    }

    SequelaType::SequelaType(Hernia::SequelaTypeEnum sequelaTypeEnum)
    {
        m_SequelaType = sequelaTypeEnum;
    }

    QString SequelaType::ToString() const
    {
        switch(m_SequelaType)
        {
        case SequelaTypeEnum::IntrOperative:
            return "Интраоперационное";
        case SequelaTypeEnum::PostOperative:
            return "Постоперационное";
        default:
            return "Не определено";
        }
    }

    int SequelaType::ToInt() const
    {
        return static_cast<int>(m_SequelaType);
    }
}
