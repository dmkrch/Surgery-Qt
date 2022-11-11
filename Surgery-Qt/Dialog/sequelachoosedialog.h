#ifndef SEQUELACHOOSEDIALOG_H
#define SEQUELACHOOSEDIALOG_H

#include <QDialog>
#include "Source/sequela.h"
#include "Source/sequelatype.h"

namespace Ui {
class SequelaChooseDialog;
}

class SequelaChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SequelaChooseDialog(QWidget *parent = nullptr);
    ~SequelaChooseDialog();

    std::optional<Hernia::Sequela> GetSequela() const;

private slots:
    void on_selectSequela_clicked();
    void on_Cancel_clicked();
    void on_sequelaTypeCombo_currentIndexChanged(int index);

private:
    Ui::SequelaChooseDialog *ui;
    std::optional<Hernia::Sequela> m_Sequela;

    std::vector<Hernia::SequelaType> m_SequelaTypes;
    std::vector<Hernia::Sequela> m_Sequelas;
};

#endif // SEQUELACHOOSEDIALOG_H
