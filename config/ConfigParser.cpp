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
        parseSlackConfig(config->slackConfig, jsonObj["slack"].toArray());
        parseLoggerConfig(config->loggerConfig, jsonObj["logger"].toObject());
        parseMonitoringConfig(config->monitoringConfig, jsonObj["monitoring"].toObject());
        parseStandGamesConfig(config->standGamesConfig, jsonObj["games"].toArray());

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
    mainConfig->release = jsonObj["release"].toBool();

    QJsonObject touchScreenData = jsonObj["screens"].toObject()["touch"].toObject();
    mainConfig->touchScreen.setX(touchScreenData["x"].toInt());
    mainConfig->touchScreen.setY(touchScreenData["y"].toInt());
    mainConfig->touchScreen.setWidth(touchScreenData["width"].toInt());
    mainConfig->touchScreen.setHeight(touchScreenData["height"].toInt());

    mainConfig->touchScreenIsSplash = touchScreenData["splashScreen"].toBool();


    QJsonObject gameScreenData = jsonObj["screens"].toObject()["game"].toObject();
    mainConfig->gameScreen.setX(gameScreenData["x"].toInt());
    mainConfig->gameScreen.setY(gameScreenData["y"].toInt());
    mainConfig->gameScreen.setWidth(gameScreenData["width"].toInt());
    mainConfig->gameScreen.setHeight(gameScreenData["height"].toInt());

    mainConfig->gameScreenIsSplash = gameScreenData["splashScreen"].toBool();


    mainConfig->qmlOnStart = jsonObj["qmlOnStart"].toString();
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
    serverConfig->serverAPI.testUser = jsonObj["api"].toObject()["testUser"].toString();
    serverConfig->serverAPI.pinNeed = jsonObj["api"].toObject()["pinNeed"].toBool();
}

void ConfigParser::parseSlackConfig(QSharedPointer<SlackFullConfig> slackConfig, const QJsonArray& jsonArray)
{
    for(auto slackChannel : jsonArray)
    {
        SlackAppConfig slackChannelconfig;
        auto slackChannelJsonObj = slackChannel.toObject();

        slackChannelconfig.enabled = slackChannelJsonObj["enabled"].toBool();
        slackChannelconfig.logChannel = slackChannelJsonObj["logChannel"].toString();
        slackChannelconfig.errorChannel = slackChannelJsonObj["errorChannel"].toString();
        slackChannelconfig.appId = slackChannelJsonObj["appId"].toInt();
        slackConfig->slackMap.insert(slackChannelconfig.appId, slackChannelconfig);
    }
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

void ConfigParser::parseStandGamesConfig(QSharedPointer<StandGamesConfig> standGamesConfig, const QJsonArray& jsonArray)
{
    for(auto jsonStandGame : jsonArray)
    {
        auto oneGameJsonObj = jsonStandGame.toObject();
        if(oneGameJsonObj["appId"].toInt() == config->mainConfig->appId)
        {
            auto data = oneGameJsonObj["data"].toArray();
            for(auto game : data)
            {
                auto gameObj = game.toObject();
                StandOneGameConfig oneGameconfig;
                oneGameconfig.category = gameObj["category"].toString();
                oneGameconfig.description = gameObj["description"].toString();

                oneGameconfig.advantage1.title = gameObj["advantage1"].toObject()["title"].toString();
                oneGameconfig.advantage1.description = gameObj["advantage1"].toObject()["description"].toString();

                oneGameconfig.advantage2.title = gameObj["advantage2"].toObject()["title"].toString();
                oneGameconfig.advantage2.description = gameObj["advantage2"].toObject()["description"].toString();

                oneGameconfig.advantage3.title = gameObj["advantage3"].toObject()["title"].toString();
                oneGameconfig.advantage3.description = gameObj["advantage3"].toObject()["description"].toString();

                qDebug()<<"==================path1==========================";
                for(auto path1 : gameObj["path1"].toArray())
                {
                    oneGameconfig.path1.push_back(QPointF(path1.toObject()["x"].toDouble(), path1.toObject()["y"].toDouble()));
                    qDebug()<<QPointF(path1.toObject()["x"].toDouble(), path1.toObject()["y"].toDouble());
                }

                qDebug()<<"==================path2==========================";
                for(auto path2 : gameObj["path2"].toArray())
                {
                    oneGameconfig.path2.push_back(QPointF(path2.toObject()["x"].toDouble(), path2.toObject()["y"].toDouble()));
                    qDebug()<<QPointF(path2.toObject()["x"].toDouble(), path2.toObject()["y"].toDouble());
                }

                qDebug()<<"==================path3==========================";
                for(auto path3 : gameObj["path3"].toArray())
                {
                    oneGameconfig.path3.push_back(QPointF(path3.toObject()["x"].toDouble(), path3.toObject()["y"].toDouble()));
                    qDebug()<<QPointF(path3.toObject()["x"].toDouble(), path3.toObject()["y"].toDouble());
                }

                standGamesConfig->games.push_back(oneGameconfig);
            }
            break;
        }
    }
}


