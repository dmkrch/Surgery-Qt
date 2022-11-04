#ifndef DATECHOOSEDIALOG_H
#define DATECHOOSEDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DateChooseDialog;
}

class DateChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateChooseDialog(QWidget *parent = nullptr);
    ~DateChooseDialog();

    std::optional<QDate> GetDate() const;

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::DateChooseDialog *ui;
    std::optional<QDate> m_Date;
};

#endif // DATECHOOSEDIALOG_H
