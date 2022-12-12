#include "paypaldialog.h"
#include "ui_paypaldialog.h"

#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrlQuery>
#include <QDir>

PaypalDialog::PaypalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaypalDialog)
{
    ui->setupUi(this);

    m_WebView = new QWebEngineView;
    ui->verticalLayout->addWidget(m_WebView);

    this->resize(600, 800);

    connect(&m_NetworkManager, &QNetworkAccessManager::finished, this,
        &PaypalDialog::onManagerFinished);

    connect(m_WebView, &QWebEngineView::loadProgress, this, &PaypalDialog::setProgress);
    connect(m_WebView, &QWebEngineView::loadFinished, this, &PaypalDialog::finishLoading);

    CreateOrderRequest();
}

void PaypalDialog::CreateOrderRequest()
{
    QNetworkRequest request(QUrl("https://api-m.sandbox.paypal.com/v1/payments/payment"));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", GetBearerHeader().toUtf8());

    QFile file("orderBody.json");

    if (file.open(QIODevice::ReadOnly))
    {
        m_NetworkManager.post(request, file.readAll());
    }
}

void PaypalDialog::onManagerFinished(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();

    QString requestState = jsonObj["state"].toString();

    if (requestState == "created")
    {
        QJsonArray arr = jsonObj["links"].toArray();

        QJsonValue executeLink = arr[2];
        m_ExecuteUrl = executeLink["href"].toString();

        QJsonValue approvalLink = arr[1];
        QString approvalURL = approvalLink["href"].toString();
        m_WebView->load(QUrl(approvalURL));
    }
    else if (requestState == "approved")
    {
        // incremenet invoice number
        QString fileName = "orderBody.json";

        QJsonDocument document = LoadJson("orderBody.json");
        QJsonObject rootObject = document.object();

        QJsonValueRef transactionsArrRef = rootObject.find("transactions").value();
        QJsonArray transactionsArr = transactionsArrRef.toArray();

        QJsonArray::iterator transactionsIterator = transactionsArr.begin();
        QJsonValueRef firstTransactionRef = transactionsIterator[0];
        QJsonObject firstTransaction = firstTransactionRef.toObject();

        // get the invoice number
        QString invoiceNumberStr = firstTransaction["invoice_number"].toString();
        int invoiceNumberInt = invoiceNumberStr.toInt();

        // now increment it
        ++invoiceNumberInt;
        firstTransaction["invoice_number"] = QString::number(invoiceNumberInt);

        // edit json document
        firstTransactionRef = firstTransaction;
        transactionsArrRef = transactionsArr;
        document.setObject(rootObject);

        // now save to file
        SaveJson(document, fileName);
        accept();
    }
    else
    {
        reject();
    }
}

void PaypalDialog::adjustTitle()
{
    if (m_LoadingPercentage <= 0 || m_LoadingPercentage >= 100)
        setWindowTitle(m_WebView->title());
    else
        setWindowTitle(QStringLiteral("%1 (%2%)").arg(m_WebView->title()).arg(m_LoadingPercentage));
}

void PaypalDialog::setProgress(int p)
{
    m_LoadingPercentage = p;
    adjustTitle();
}

void PaypalDialog::finishLoading(bool)
{
    m_LoadingPercentage = 100;
    adjustTitle();

    // here we get url. If it located us to google.com - take buyer id
    QString host = m_WebView->url().host();

    if (host == "www.google.com")
    {
        // take buyer id and send get request with it
        // then close this widget
        QUrlQuery query(m_WebView->url());
        QString payerID = query.queryItemValue("PayerID");

        QString requestBody = "{\"payer_id\": \"";
        requestBody += payerID;
        requestBody += "\"}";

        QUrl url;
        url.setUrl(m_ExecuteUrl);

        QNetworkRequest request(url);
        request.setRawHeader("Content-Type", "application/json");
        request.setRawHeader("Authorization", GetBearerHeader().toUtf8());
        m_NetworkManager.post(request, requestBody.toUtf8());
    }
}

QString PaypalDialog::GetBearer() const
{
    QFile file(":/new/text/credentials.json");

    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray bytes = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObj = document.object();
        return jsonObj["bearer"].toString();
    }

    return QString();
}

QString PaypalDialog::GetBearerHeader() const
{
    return QString("Bearer ") + GetBearer();
}

PaypalDialog::~PaypalDialog()
{
    delete ui;
}
