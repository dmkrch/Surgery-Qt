#ifndef DIAGNOSISCHOOSEDIALOG_H
#define DIAGNOSISCHOOSEDIALOG_H

#include <QDialog>
#include "Source/diagnosis.h"

namespace Ui {
class DiagnosisChooseDialog;
}

class DiagnosisChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiagnosisChooseDialog(QWidget *parent = nullptr);
    ~DiagnosisChooseDialog();

    std::optional<Hernia::Diagnosis> GetDiagnosis() const;

private slots:
    void on_selectDiagnosis_clicked();
    void on_Cancel_clicked();

private:
    Ui::DiagnosisChooseDialog *ui;

    std::optional<Hernia::Diagnosis> m_CurrentDiagnosis;
    std::vector<Hernia::DiagnosisLMFParam> m_LMFs;
};

#endif // DIAGNOSISCHOOSEDIALOG_H
