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
        //        qDebug()<<configData<<endl;
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


        if(!wasParsingError)
        {
            config->setRawData(configData);
            config->valid = true;
            emit parseComplete(config);
        }
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
    mainConfig->videoEXT = jsonObj["videoEXT"].toString();

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
    rfidConfig->type = jsonObj["type"].toString();
    rfidConfig->writeValidation = jsonObj["validation"].toString();
    rfidConfig->beepEnabled = jsonObj["beepEnabled"].toBool();
}

void ConfigParser::parseMindwaveConfig(QSharedPointer<MindwaveConfig> mindwaveConfig, const QJsonObject& jsonObj)
{
    mindwaveConfig->ip = jsonObj["ip"].toString();
    mindwaveConfig->port = jsonObj["port"].toInt();
    mindwaveConfig->autoConnect = jsonObj["autoConnect"].toBool();
    mindwaveConfig->delimeter = jsonObj["delimeter"].toString();
    mindwaveConfig->initialCommand = jsonObj["initialCommand"].toString();
    mindwaveConfig->authCommand = jsonObj["authCommand"].toString();
    mindwaveConfig->type = jsonObj["type"].toString();
    mindwaveConfig->timeoutMills = jsonObj["timeout"].toInt();
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
    bool isStandHasGames = false;

    for(auto jsonStandGame : jsonArray)
    {
        auto oneGameJsonObj = jsonStandGame.toObject();
        if(oneGameJsonObj["appId"].toInt() == config->mainConfig->appId)
        {
            // cola game parsing

            auto data = oneGameJsonObj["mainGame"].toArray();
            for(auto game : data)
            {
                auto gameObj = game.toObject();
                StandOneGameConfig oneGameconfig;
                oneGameconfig.category = gameObj["category"].toString();
                oneGameconfig.description = gameObj["description"].toString();
                oneGameconfig.descriptionWin = gameObj["descriptionwin"].toString();
                oneGameconfig.imageWinName = gameObj["imagewinpath"].toString();
                oneGameconfig.iconName = gameObj["iconpath"].toString();

                auto stagesJson = gameObj["stages"].toArray();

                for(auto oneStageJson : stagesJson)
                {
                    OneStageConfig oneStage;
                    auto advantageObject = oneStageJson.toObject()["advantage"].toObject();
                    oneStage.advantage.title = advantageObject["title"].toString();
                    oneStage.advantage.description = advantageObject["description"].toString();
                    oneStage.advantage.descriptionMap = advantageObject["descriptionmap"].toString();
                    oneStage.advantage.videoPath = advantageObject["videoPath"].toString();
                    for(auto path: oneStageJson.toObject()["path"].toArray())
                    {
                        oneStage.path.push_back(QPointF(path.toObject()["x"].toDouble(), path.toObject()["y"].toDouble()));
                    }

                    oneGameconfig.stages.push_back(oneStage);
                }

                auto startPathJson = gameObj["startPath"].toArray();
                for(auto path: startPathJson)
                {
                    auto x = (path.toObject()["x"].toDouble());
                    auto y = (path.toObject()["y"].toDouble());
                    oneGameconfig.startPath.push_back(QPointF(x, y));
                }

                auto finalPathJson = gameObj["finalPath"].toArray();
                for(auto path: finalPathJson)
                {
                    auto x = (path.toObject()["x"].toDouble());
                    auto y = (path.toObject()["y"].toDouble());
                    oneGameconfig.finalPath.push_back(QPointF(x, y));
                }

                standGamesConfig->games.push_back(oneGameconfig);
            }

            // super game parsing

            auto superGameData = oneGameJsonObj["superGame"].toObject();
            SuperGameConfig superGameConfig;
            superGameConfig.time = superGameData["time"].toInt();

            for(auto path: superGameData["path"].toArray())
            {
                superGameConfig.path.push_back(QPointF(path.toObject()["x"].toDouble(), path.toObject()["y"].toDouble()));
            }
            standGamesConfig->superGame = superGameConfig;
            isStandHasGames = true;

            break;
        }
    }

    if(!isStandHasGames)
    {
        wasParsingError = true;
        parseError("No games for this stand id = " + QString::number(config->mainConfig->appId));
    }
}
