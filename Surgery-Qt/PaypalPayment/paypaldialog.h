#ifndef PAYPALDIALOG_H
#define PAYPALDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QWebEngineView>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QFile>

namespace Ui {
class PaypalDialog;
}

class PaypalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaypalDialog(QWidget *parent = nullptr);
    void CreateOrderRequest();
    ~PaypalDialog();

private slots:
    void onManagerFinished(QNetworkReply * reply);
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);

private:
    QString GetBearer() const;
    QString GetBearerHeader() const;
    QString GetPaypalOrderFilePath() const;
    QString GetPaypalCredentialsFilePath() const;
    void IncrementInvoiceNumber();

    QJsonDocument LoadJson(QString fileName);
    void SaveJson(QJsonDocument document, QString fileName);

private:
    Ui::PaypalDialog *ui;
    QNetworkAccessManager m_NetworkManager;
    QWebEngineView * m_WebView;
    QString m_ExecuteUrl;
    int m_LoadingPercentage = 0;
    QDialog m_WaitDialog;
};

#endif // PAYPALDIALOG_H
