#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

namespace Hernia
{
    class Operation
    {
    public:
        Operation();
        Operation(int id, const QString & title);

        QString GetOperationTitle() const;
        int GetId() const;

    private:
        int m_Id;
        QString m_Title;
    };
}

#endif // OPERATION_H
