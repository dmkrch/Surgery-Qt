#include "gender.h"

namespace Hernia
{
    Gender::Gender()
        : m_Gender(GenderEnum::Undefined)
    {

    }

    Gender::Gender(GenderEnum genderEnum)
    {
        m_Gender = genderEnum;
    }

    QString Gender::ToString() const
    {
        switch(m_Gender)
        {
        case GenderEnum::Male:
            return QString("Мужской");
        case GenderEnum::Female:
            return QString("Женский");
        default:
            return QString("Не определено");
        }
    }

  GenderEnum Gender::GetGenderEnum() const
  {
      return m_Gender;
  }
}
