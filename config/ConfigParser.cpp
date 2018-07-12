#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug.h>

ConfigParser::ConfigParser()
{
    config.reset(new Config());
}

ConfigParser::~ConfigParser()
{

}

void ConfigParser::parse(const QString& configData)
{
    try
    {
        //        qDebug()<<"configData................"<<endl;
        //        qDebug()<<configData <<endl;
        //        qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        parseMainConfig(config->mainConfig, jsonObj);
        parseRFIDConfig(config->rfidConfig, jsonObj["rfid"].toObject());
        parseMindwaveConfig(config->mindwaveConfig, jsonObj["mindwave"].toObject());
        parseServerConfig(config->serverConfig, jsonObj["server"].toObject());
        parseSlackConfig(config->slackConfig, jsonObj["slack"].toObject());
        parseLoggerConfig(config->loggerConfig, jsonObj["logger"].toObject());
        parseMonitoringConfig(config->monitoringConfig, jsonObj["monitoring"].toObject());

        config->setRawData(configData);
        config->valid = true;
        emit parseComplete(config);
    }
    catch(...)
    {
        config->valid = false;
        qDebug()<<"parsing error................";
    }
}

void ConfigParser::parseMainConfig(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj)
{
    mainConfig->version = jsonObj["version"].toInt();
    mainConfig->configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    mainConfig->needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    mainConfig->appId = jsonObj["appId"].toInt();
    mainConfig->workingDirectory = jsonObj["workingDirectory"].toString();
    mainConfig->folderSeparator = jsonObj["folderSeparator"].toString();
    mainConfig->appName = jsonObj["appName"].toString();

    QJsonObject touchScreenData = jsonObj["screens"].toObject()["touch"].toObject();
    mainConfig->touchScreen.setX(touchScreenData["x"].toInt());
    mainConfig->touchScreen.setY(touchScreenData["y"].toInt());
    mainConfig->touchScreen.setWidth(touchScreenData["width"].toInt());
    mainConfig->touchScreen.setHeight(touchScreenData["height"].toInt());

    QJsonObject gameScreenData = jsonObj["screens"].toObject()["game"].toObject();
    mainConfig->gameScreen.setX(gameScreenData["x"].toInt());
    mainConfig->gameScreen.setY(gameScreenData["y"].toInt());
    mainConfig->gameScreen.setWidth(gameScreenData["width"].toInt());
    mainConfig->gameScreen.setHeight(gameScreenData["height"].toInt());
}

void ConfigParser::parseRFIDConfig(QSharedPointer<RFIDConfig> rfidConfig, const QJsonObject& jsonObj)
{
    rfidConfig->serialPort = jsonObj["serialPort"].toString();
    rfidConfig->baudRate = jsonObj["baudRate"].toInt();
    rfidConfig->autoConnect = jsonObj["autoConnect"].toBool();
    rfidConfig->portKeyWord = jsonObj["portKeyWord"].toString();
    rfidConfig->useKeyword = jsonObj["useKeyword"].toBool();
}

void ConfigParser::parseMindwaveConfig(QSharedPointer<MindwaveConfig> mindwaveConfig, const QJsonObject& jsonObj)
{
    mindwaveConfig->ip = jsonObj["ip"].toString();
    mindwaveConfig->port = jsonObj["port"].toInt();
    mindwaveConfig->autoConnect = jsonObj["autoConnect"].toBool();
    mindwaveConfig->delimeter = jsonObj["delimeter"].toString();
    mindwaveConfig->initialCommand = jsonObj["initialCommand"].toString();
    mindwaveConfig->authCommand = jsonObj["authCommand"].toString();
}

void ConfigParser::parseServerConfig(QSharedPointer<ServerConfig> serverConfig, const QJsonObject& jsonObj)
{   
    serverConfig->url = jsonObj["url"].toString();
    serverConfig->requestTimemoutInterval = jsonObj["requestTimemoutInterval"].toInt();
    serverConfig->requestTryCount = jsonObj["requestCount"].toInt();
}

void ConfigParser::parseSlackConfig(QSharedPointer<SlackConfig> slackConfig, const QJsonObject& jsonObj)
{
    slackConfig->logChannel = jsonObj["logChannel"].toString();
    slackConfig->errorChannel = jsonObj["errorChannel"].toString();
    slackConfig->enabled = jsonObj["enabled"].toBool();
}

void ConfigParser::parseMonitoringConfig(QSharedPointer<MonitoringConfig> monitoringConfig, const QJsonObject& jsonObj)
{
     monitoringConfig->memoryCheckMills = jsonObj["memoryCheckMills"].toInt();
     monitoringConfig->enabled = jsonObj["enabled"].toBool();
}

void ConfigParser::parseLoggerConfig(QSharedPointer<LoggerConfig> loggerConfig, const QJsonObject& jsonObj)
{
    loggerConfig->localEnabled = jsonObj["local"].toObject()["enabled"].toBool();
    loggerConfig->localPath = jsonObj["local"].toObject()["path"].toString();
}
