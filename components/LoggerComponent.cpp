#include "LoggerComponent.h"
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>

LoggerComponent::LoggerComponent(QObject *parent) : BaseComponent(parent)
{
    name = "Logger";

    slackComponent.reset(new SlackComponent());
    connect(slackComponent.data(), SIGNAL(slackNotifyResponse(const QString&)), this, SLOT(onSlackNotifyResponse(const QString&)));
}

LoggerComponent::~LoggerComponent()
{
    disconnect(slackComponent.data(), SIGNAL(slackNotifyResponse(const QString&)), this, SLOT(onSlackNotifyResponse(const QString&)));
}

void LoggerComponent::setConfig(ConfigPtr value)
{
    BaseComponent::setConfig(value);
    appId = value->mainConfig->appId;
    appName = value->mainConfig->appName;
    slackComponent->setConfig(value);
}

void LoggerComponent::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("logger", this);
}

void LoggerComponent::log(const QString& message, LogType type, LogRemoteType remoteType, bool saveLocal)
{
    qDebug()<<message;

    QString color;
    bool isError = false;

    switch(type)
    {
    case LogType::Verbose:
        color = "black";
        break;

    case LogType::Error:
        color = "red";
        isError = true;
        break;

    case LogType::Warning:
        color = "yellow";
        break;
    }

    switch(remoteType)
    {
    case LogRemoteType::Slack:
        slackComponent->sendMessage(createSlackMessage(message), isError);
        break;

    case LogRemoteType::Server:
        break;
    }

    if(saveLocal && config->loggerConfig->localEnabled)
    {
        logTofile(message);
    }
}

void LoggerComponent::onSlackNotifyResponse(const QString& message)
{
    if(config->loggerConfig->localEnabled)
    {
        logTofile("Slack notify : " + message);
    }
}

void LoggerComponent::logTofile(const QString& message)
{
    QFile file(getLocalLogAbsoluteFilePath());
    file.open(QIODevice::Append | QIODevice::Text);
    if(file.isOpen())
    {
        QTextStream out(&file);
        out<<createLocalMessage(message)<<endl;
        file.close();
    }
}

QString LoggerComponent::createSlackMessage(const QString& message) const
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = "[" + now.date().toString() + " " + now.time().toString() + ": ";
    QString appData =  appName + " " + QString::number(appId) + "] ";
    return  currentTime + appData + message;
}

QString LoggerComponent::createLocalMessage(const QString& message) const
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = "[" + now.time().toString() + ": ";
    QString appData =  appName + " " + QString::number(appId) + "] ";
    QString localMessage = currentTime + appData + message;
    return localMessage;
}

QString LoggerComponent::getLocalLogAbsoluteFilePath() const
{
    QDateTime now = QDateTime::currentDateTime();
    QString fileFullPath = getLocalLogDirPath() + "/" + now.date().toString(logFormat) +".txt";
    return fileFullPath;
}

QString LoggerComponent::getLocalLogDirPath() const
{
   return QCoreApplication::applicationDirPath() + "/" + config->loggerConfig->localPath;
}

void LoggerComponent::start()
{
    if(!QDir(getLocalLogDirPath()).exists())
    {
        QDir().mkdir(getLocalLogDirPath());
    }
}

void LoggerComponent::stop()
{

}

QString LoggerComponent::getName() const
{
    return "Logger";
}
