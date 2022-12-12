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

enum class RequestType
{
    CreateOrder,
    ApproveOrder,
    ExecuteOrder
};

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

    QJsonDocument LoadJson(QString fileName)
    {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::ReadOnly);
        return QJsonDocument().fromJson(jsonFile.readAll());
    }

    void SaveJson(QJsonDocument document, QString fileName)
    {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(document.toJson());
    }

private:
    Ui::PaypalDialog *ui;
    QNetworkAccessManager m_NetworkManager;
    QWebEngineView * m_WebView;
    QString m_ExecuteUrl;
    int m_LoadingPercentage = 0;
};

#endif // PAYPALDIALOG_H
