#ifndef HANDLEDOPERATIONSMODEL_H
#define HANDLEDOPERATIONSMODEL_H

#include "QObject"

#include "Source/handledoperation.h"

class HandledOperationsModel : public QObject
{
    Q_OBJECT

public:
    HandledOperationsModel();

    void AddHandledOperation(const Hernia::HandledOperation & handledOperation);
    void DeleteHandledOperation(int operationId);

    const std::vector<Hernia::HandledOperation> & GetData() const;

signals:
    void dataModified();

private:
    std::vector<Hernia::HandledOperation> m_HandledOperations;
};

#endif // HANDLEDOPERATIONSMODEL_H
