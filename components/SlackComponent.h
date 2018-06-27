#ifndef SLACKCOMPONENT_H
#define SLACKCOMPONENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "components/BaseComponent.h"
#include "config/Config.h"
#include "core/Types.h"

class SlackComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit SlackComponent(QObject *parent = nullptr);
    void sendMessage(const QString& msg, LogType type);
    void setConfig(const SlackConfig& config);

private:
   QNetworkAccessManager* networkManager;
   SlackConfig slackConfig;

signals:

private slots:
   void httpRequestSuccessHandler(QNetworkReply* reply);
   void onRequestFailed();
};

#endif // SLACKCOMPONENT_H
