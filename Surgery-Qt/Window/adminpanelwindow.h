#ifndef ADMINPANELWINDOW_H
#define ADMINPANELWINDOW_H

#include <QWidget>

namespace Ui {
class AdminPanelWindow;
}

class AdminPanelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanelWindow(QWidget *parent = nullptr);
    ~AdminPanelWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminPanelWindow *ui;
};

#endif // ADMINPANELWINDOW_H
