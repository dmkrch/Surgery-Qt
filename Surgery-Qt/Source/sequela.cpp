#include "sequela.h"

namespace Hernia
{
    Sequela::Sequela()
        : m_Id(0)
    {

    }

    Sequela::Sequela(int id, const QString & title, SequelaType sequelaType)
    {
        m_Id = id;
        m_Title = title;
        m_SequelaType = sequelaType;
    }

    QString Sequela::ToString() const
    {
        return QString(m_SequelaType.ToString() + ": " + m_Title);
    }

    void Sequela::SetId(int id)
    {
        m_Id = id;
    }

    void Sequela::SetTitle(const QString & title)
    {
        m_Title = title;
    }

    void Sequela::SetSequelaType(SequelaType sequelaType)
    {
        m_SequelaType = sequelaType;
    }

    SequelaType Sequela::GetSeqType() const
    {
        return m_SequelaType;
    }

    QString Sequela::GetTitle() const
    {
        return m_Title;
    }

    int Sequela::GetId() const
    {
        return m_Id;
    }
}

