#ifndef SEQUELATYPE_H
#define SEQUELATYPE_H

#include <QString>

namespace Hernia
{
    enum class SequelaTypeEnum
    {
        IntrOperative = 1,
        PostOperative = 2,
        Undefined = 3
    };

    class SequelaType
    {
    public:
        SequelaType();
        explicit SequelaType(SequelaTypeEnum sequelaTypeEnum);

        QString ToString() const;
        int ToInt() const;

    private:
        SequelaTypeEnum m_SequelaType;
    };
}
#endif // SEQUELATYPE_H
