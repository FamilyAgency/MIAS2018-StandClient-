#include "SlackComponent.h"
#include <QHttpPart>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>

SlackComponent::SlackComponent(QObject *parent) : BaseComponent(parent)
{
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestSuccessHandler(QNetworkReply*)));
   // connect(networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(onSslError(QNetworkReply*, QList<QSslError>)));
}

void SlackComponent::setConfig(const SlackConfig& config)
{
    slackConfig = config;
    //emit configChanged();
}

void SlackComponent::sendMessage(const QString& msg, LogType type)
{
    QString channel = slackConfig.logChannel;
    if(type == LogType::Error)
    {
        channel = slackConfig.errChannel;
    }

    QJsonObject recordObject;
    recordObject.insert("text", QJsonValue::fromVariant(msg));

    QJsonDocument doc(recordObject);
    QByteArray jsonString = doc.toJson();
    QByteArray postDataSize = QByteArray::number(jsonString.size());
    QUrl serviceURL(channel);
    QNetworkRequest request(serviceURL);

    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);
   // QNetworkReply * reply = networkManager->post(request, jsonString);
}

void SlackComponent::httpRequestSuccessHandler(QNetworkReply* reply)
{
    //if(reply->url().host() == SERVER_HOST)
    {
        QByteArray ba = reply->readAll();
        QString s_data = QString::fromUtf8(ba);
        //QJsonDocument jsonResponse = QJsonDocument::fromJson(ba);
        //QJsonObject jsonObject = jsonResponse.object();
        //QString status = jsonObject["status"].toString();
        qDebug() << "server answered :::  " << s_data;
        reply->deleteLater();
        return;
    }

    if (reply->error() != QNetworkReply::NoError )
    {
        QByteArray ba = reply->readAll();
        QString s_data = QString::fromUtf8(ba);

        qDebug() << "Request failed, " << reply->errorString();
        return;
    }
    else
    {
        QByteArray ba = reply->readAll();
        QString s_data = QString::fromUtf8(ba);
        qDebug()<<"server message :: "<< s_data;
    }

    reply->deleteLater();
}

void SlackComponent::onRequestFailed()
{
    qDebug()<<"request failed, we tried several times((( ";
}


