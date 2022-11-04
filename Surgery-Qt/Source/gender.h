#ifndef GENDER_H
#define GENDER_H

#include <QString>

namespace Hernia
{
    enum class GenderEnum
    {
        Male = 1,
        Female = 2,
        Undefined = 3
    };

    class Gender
    {
    public:
        Gender();
        explicit Gender(GenderEnum genderEnum);

        QString ToString() const;
        GenderEnum GetGenderEnum() const;

    private:
        GenderEnum m_Gender;
    };
}

#endif // GENDER_H
