#include "surgeon.h"

namespace Hernia
{
    Surgeon::Surgeon()
        : m_Gender(GenderEnum::Undefined)
    {

    }

    Surgeon::Surgeon(int id, QString name, Gender gender)
    {
        m_Id = id;
        m_Name = name;
        m_Gender = gender;
    }

    const QString& Surgeon::GetName() const
    {
        return m_Name;
    }

    Gender Surgeon::GetGender() const
    {
        return m_Gender;
    }

   int Surgeon::GetId() const
   {
        return m_Id;
   }

   void Surgeon::SetId(int id)
   {
       m_Id = id;
   }
}
