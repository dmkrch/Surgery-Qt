#ifndef OPERATIONDELETEDIALOG_H
#define OPERATIONDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class OperationDeleteDialog;
}

class OperationDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OperationDeleteDialog(QWidget *parent = nullptr);
    ~OperationDeleteDialog();

    int GetOperationId() const;

private slots:
    void on_buttonDelete_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::OperationDeleteDialog *ui;
};

#endif // OPERATIONDELETEDIALOG_H
