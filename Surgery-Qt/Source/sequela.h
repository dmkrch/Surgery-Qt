#ifndef SEQUELA_H
#define SEQUELA_H

#include <QString>
#include "sequelatype.h"

namespace Hernia
{
    class Sequela
    {
    public:
        Sequela();
        Sequela(int m_Id, const QString & title, const SequelaType & sequelaType);

        QString ToString() const;

        void SetId(int id);
        void SetTitle(const QString & title);
        void SetSequelaType(SequelaType sequelaType);

        SequelaType GetSeqType() const;
        QString GetTitle() const;
        int GetId() const;

    private:
        int m_Id;
        QString m_Title;
        SequelaType m_SequelaType;
    };
}

#endif // SEQUELA_H
