#include "datechoosedialog.h"
#include "ui_datechoosedialog.h"

DateChooseDialog::DateChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateChooseDialog)
{
    ui->setupUi(this);
}

DateChooseDialog::~DateChooseDialog()
{
    delete ui;
}

std::optional<QDate> DateChooseDialog::GetDate() const
{
    return m_Date;
}

void DateChooseDialog::on_calendarWidget_clicked(const QDate &date)
{
    m_Date = date;
    accept();
}
