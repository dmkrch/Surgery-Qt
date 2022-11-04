#ifndef SURGEONADDDIALOG_H
#define SURGEONADDDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include "ModelView/Model/genderlistmodel.h"
#include "Source/surgeon.h"

namespace Ui {
class SurgeonAddDialog;
}

class SurgeonAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SurgeonAddDialog(QWidget *parent = nullptr);
    ~SurgeonAddDialog();

    std::optional<Hernia::Surgeon> GetSurgeon() const;

private slots:
    void OnCancelButtonClicked();
    void OnAddButtonClicked();

private:
    Ui::SurgeonAddDialog *ui;
    GenderListModel *m_GendersListModel;
    std::optional<Hernia::Surgeon> m_SurgeonToAdd;
};

#endif // SURGEONADDDIALOG_H
