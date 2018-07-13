#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>
#include <QTimer>

class HTTPClient : public QObject
{
    Q_OBJECT
public:
    explicit HTTPClient(QObject *parent = nullptr);
    virtual ~HTTPClient();
    bool getRequestStatus() const;
    void runGetRequest(const QString& url);
    void runPostRequest(const QNetworkRequest& request, const QByteArray& data);
    void runDeleteRequest(const QNetworkRequest& request);
    void runPutRequest(const QNetworkRequest& request, const QByteArray& data);

    void setTimemoutInterval(int interval);
    void setRequestTryCount(int requestTryCount);

signals:
    void httpRequestSuccess(const QString& data);
    void httpRequestFailed(const QString& data);

public slots:
    void httpRequestSuccessHandler(QNetworkReply*);
    void httpRequestErrorHandler(QNetworkReply::NetworkError);
    void sslErrorHandler(QNetworkReply*, const QList<QSslError> &errors);

private:
     QNetworkAccessManager *networkManager;
     QChar toCyrConverter(const QString& unicode);
     QTimer* timeoutTimer;
     QNetworkReply* httpReply = nullptr;
     int requestTryCount = 1;
     int requestTimemoutInterval = 1;

private slots:
     void onTimeoutHandle();
};

#endif // HTTPCLIENT_H
