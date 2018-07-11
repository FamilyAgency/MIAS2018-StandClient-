#include "HTTPClient.h"
#include <QThread.h>
#include <QTextCodec.h>
#include "tools/StringTools.h"

HTTPClient::HTTPClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    networkManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    networkManager->moveToThread(QThread::currentThread());

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
    //connect(networkManager, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpRequestErrorHandler(QNetworkReply::NetworkError)));
    connect(networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(sslErrorHandler(QNetworkReply*, QList<QSslError>)));
}

HTTPClient::~HTTPClient()
{
    if(networkManager)
    {
        disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
        //disconnect(networkManager, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpRequestErrorHandler(QNetworkReply::NetworkError)));
        disconnect(networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(sslErrorHandler(QNetworkReply*, QList<QSslError>)));

        delete networkManager;
    }
}

void HTTPClient::runGetRequest(const QString& URL)
{
    QNetworkRequest request = QNetworkRequest(QUrl(URL));
    //httpReply =
    networkManager->get(request);
}

void HTTPClient::runPostRequest(const QNetworkRequest& request, const QByteArray& data)
{
    networkManager->post(request, data);  
}

void HTTPClient::runDeleteRequest(const QNetworkRequest& request)
{
    networkManager->deleteResource(request);
}

void HTTPClient::httpRequestSuccessHandler(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError )
    {
        qDebug() << "Request failed, " << reply->readAll();
        emit httpRequestFailed(reply->errorString());
    }
    else
    {
        QByteArray ba = reply->readAll();
        StringTools stringTools;
        QString modifyedString = stringTools.convertUnicodeToCyrillic(ba);

        emit httpRequestSuccess(modifyedString);
    }

    reply->deleteLater();
}

void HTTPClient::httpRequestErrorHandler(QNetworkReply::NetworkError data)
{

}

void HTTPClient::sslErrorHandler(QNetworkReply* reply,const QList<QSslError> &errors)
{
    foreach ( const QSslError &e, errors) {
        qDebug() << "SSL Error:" << e.errorString();
    }

    reply->ignoreSslErrors(errors);
    emit httpRequestFailed("SSL Error");
}
