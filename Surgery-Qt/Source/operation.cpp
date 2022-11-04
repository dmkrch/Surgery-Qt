#include "operation.h"

namespace Hernia
{
    Operation::Operation()
        : m_Id(0)
    {

    }

    Operation::Operation(int id, const QString & title)
    {
        m_Id = id;
        m_Title = title;
    }

    QString Operation::GetOperationTitle() const
    {
        return m_Title;
    }

    int Operation::GetOperationId() const
    {
        return m_Id;
    }
}
