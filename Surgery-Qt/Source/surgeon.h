#ifndef SURGEON_H
#define SURGEON_H

#include <QString>
#include "gender.h"

namespace Hernia
{
    class Surgeon
    {
    public:
        Surgeon();
        Surgeon(int id, const QString & name, const Gender & gender);

        const QString& GetName() const;
        Gender GetGender() const;
        int GetId() const;

        void SetId(int id);
    private:
        int m_Id;
        QString m_Name;
        Gender m_Gender;
    };
}

#endif // SURGEON_H
