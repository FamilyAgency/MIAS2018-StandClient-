#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QDir>

ConfigParser::ConfigParser()
{
    QDir dir = QDir(QCoreApplication::applicationDirPath());
    dir.cdUp();

    QString iniPath = dir.path() + "/Settings.ini";
    settings = new QSettings(iniPath, QSettings::IniFormat);

    qDebug()<<"iniPath"<<iniPath;


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
        parseStandAnimConfig(config->standAnimConfig, jsonObj["animations"].toArray());
        parseAdvantagesConfig(config->advantagesConfig, jsonObj["advantages"].toArray());
        parseComplexityConfig(config->complexityConfig, jsonObj["complexity"].toObject());


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

    settings->beginGroup("Screens.Game");
    mainConfig->gameScreen.setX(settings->value("x").toInt());
    mainConfig->gameScreen.setY(settings->value("y").toInt());
    mainConfig->gameScreen.setWidth(settings->value("width").toInt());
    mainConfig->gameScreen.setHeight(settings->value("height").toInt());
    mainConfig->gameScreenIsSplash = settings->value("splashScreen").toBool();
    settings->endGroup();

    settings->beginGroup("Screens.Touch");
    mainConfig->touchScreen.setX(settings->value("x").toInt());
    mainConfig->touchScreen.setY(settings->value("y").toInt());
    mainConfig->touchScreen.setWidth(settings->value("width").toInt());
    mainConfig->touchScreen.setHeight(settings->value("height").toInt());
    mainConfig->touchScreenIsSplash = settings->value("splashScreen").toBool();
    settings->endGroup();

    settings->beginGroup("Main");
    mainConfig->qmlOnStart  = settings->value("qmlOnStart").toString();
    mainConfig->noname = settings->value("noname").toBool();
    mainConfig->appName = settings->value("appName").toString();
    mainConfig->release = settings->value("release").toBool();
    mainConfig->videoEXT = settings->value("videoEXT").toString();
    mainConfig->configUpdateUrl = settings->value("configUpdateUrl").toString();
    mainConfig->needRemoteUpdate = settings->value("needRemoteUpdate").toBool();
    mainConfig->appId = settings->value("appId").toInt();
    mainConfig->workingDirectory = settings->value("workingDirectory").toString();
    mainConfig->folderSeparator = settings->value("folderSeparator").toString();
    settings->endGroup();

    qDebug()<<" mainConfig->noname  "<< mainConfig->noname;
}

void ConfigParser::parseRFIDConfig(QSharedPointer<RFIDConfig> rfidConfig, const QJsonObject& jsonObj)
{  
    settings->beginGroup("RFID");
    rfidConfig->autoConnect = settings->value("autoConnect").toBool();
    rfidConfig->type = settings->value("type").toString();
    settings->endGroup();

    settings->beginGroup("RFID.Serial");
    rfidConfig->baudRate = settings->value("baudRate").toInt();
    rfidConfig->serialPort = settings->value("serialPort").toString();
    rfidConfig->portKeyWord = settings->value("portKeyWord").toString();
    rfidConfig->useKeyword = settings->value("useKeyword").toBool();
    settings->endGroup();

    settings->beginGroup("RFID.Winscard");
    rfidConfig->beepEnabled = settings->value("beepEnabled").toBool();
    if(rfidConfig->type == "winscard")
    {
        rfidConfig->type = settings->value("name").toString();
    }
    settings->endGroup();
    qDebug()<<"rfidConfig->type "<<rfidConfig->type;
    qDebug()<<"rfidConfig->beepEnabled "<<rfidConfig->beepEnabled;


    settings->beginGroup("RFID.StandAPI");
    rfidConfig->writeValidation = jsonObj["validation"].toString();
    settings->endGroup();
}

void ConfigParser::parseMindwaveConfig(QSharedPointer<MindwaveConfig> mindwaveConfig, const QJsonObject& jsonObj)
{
    settings->beginGroup("Mindwave");
    mindwaveConfig->type = settings->value("type").toString();
    mindwaveConfig->timeoutMills = settings->value("timeout").toInt();
    mindwaveConfig->autoConnect = settings->value("autoConnect").toBool();
    settings->endGroup();

    settings->beginGroup("Mindwave.Serial");
    mindwaveConfig->com = settings->value("com").toString();
    settings->endGroup();

    settings->beginGroup("Mindwave.TCP");
    mindwaveConfig->ip = settings->value("ip").toString();
    mindwaveConfig->port = settings->value("port").toInt();
    mindwaveConfig->delimeter = settings->value("delimeter").toString();
    mindwaveConfig->authCommand = settings->value("authCommand").toString();
    mindwaveConfig->initialCommand = settings->value("initialCommand").toString();
    settings->endGroup();
}

void ConfigParser::parseServerConfig(QSharedPointer<ServerConfig> serverConfig, const QJsonObject& jsonObj)
{
    settings->beginGroup("Server");
    serverConfig->url = settings->value("url").toString();
    serverConfig->requestTimemoutInterval = settings->value("requestTimemoutInterval").toInt();
    serverConfig->requestTryCount = settings->value("requestCount").toInt();
    settings->endGroup();

    settings->beginGroup("Server.API");
    serverConfig->serverAPI.testUser  = settings->value("testUser").toString();
    serverConfig->serverAPI.pinNeed = settings->value("pinNeed").toBool();
    settings->endGroup();

    qDebug()<<"serverConfig->url "<<serverConfig->url;
    qDebug()<<"serverConfig->requestTimemoutInterval "<<serverConfig->requestTimemoutInterval;
    qDebug()<<"serverConfig->requestTryCount "<<serverConfig->requestTryCount;
    qDebug()<<"serverConfig->serverAPI.testUser "<<serverConfig->serverAPI.testUser;
    qDebug()<<"serverConfig->serverAPI.pinNeed "<<serverConfig->serverAPI.pinNeed;
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
    settings->beginGroup("Monitoring");
    monitoringConfig->memoryCheckMills = settings->value("memoryCheckMills").toInt();
    monitoringConfig->enabled  = settings->value("enabled").toBool();
    settings->endGroup();

    qDebug()<<"monitoringConfig->memoryCheckMills "<<monitoringConfig->memoryCheckMills;
    qDebug()<<"monitoringConfig->enabled "<< monitoringConfig->enabled;
}

void ConfigParser::parseLoggerConfig(QSharedPointer<LoggerConfig> loggerConfig, const QJsonObject& jsonObj)
{    
    settings->beginGroup("Logger.Local");
    loggerConfig->localPath = settings->value("path").toString();
    loggerConfig->localEnabled  = settings->value("enabled").toBool();
    settings->endGroup();

    qDebug()<<"loggerConfig->localPath "<<loggerConfig->localPath;
    qDebug()<<"loggerConfig->localEnabled "<<loggerConfig->localEnabled;
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
                // oneGameconfig.category = gameObj["category"].toString();// todo check
                oneGameconfig.description = gameObj["description"].toString();
                oneGameconfig.descriptionWin = gameObj["descriptionwin"].toString();
                oneGameconfig.imageWinName = gameObj["imagewinpath"].toString();
                oneGameconfig.iconName = gameObj["iconpath"].toString();

                auto stagesJson = gameObj["stages"].toArray();

                for(auto oneStageJson : stagesJson)
                {
                    OneStageConfig oneStage;
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

                //final path

                OneStageConfig oneStage;
                auto finalPathJson = gameObj["finalPath"].toArray();
                for(auto path: finalPathJson)
                {
                    auto x = (path.toObject()["x"].toDouble());
                    auto y = (path.toObject()["y"].toDouble());
                    oneStage.path.push_back(QPointF(x, y));
                }


                oneGameconfig.stages.push_back(oneStage);
                //



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

void ConfigParser::parseStandAnimConfig(QSharedPointer<StandAnimConfig> standAnimConfig, const QJsonArray& jsonArray)
{

    for(auto jsonStandAnim : jsonArray)
    {
        auto oneAnimMapJsonObj = jsonStandAnim.toObject();
        if(oneAnimMapJsonObj["appId"].toInt() == config->mainConfig->appId)
        {
            auto data = oneAnimMapJsonObj["mapAnimations"].toArray();

            for(auto anims : data)
            {
                StandOneAnimConfig oneAnimation;
                auto animsObj = anims.toObject();
                oneAnimation.x = animsObj["x"].toInt();
                oneAnimation.y = animsObj["y"].toInt();
                oneAnimation.path = animsObj["path"].toString();
                oneAnimation.frames = animsObj["frames"].toInt();

                standAnimConfig->animations.push_back(oneAnimation);
            }

            break;
        }
    }
}

void ConfigParser::parseAdvantagesConfig(QSharedPointer<AdvantagesConfig> advantagesConfig, const QJsonArray& jsonArray)
{
    for(auto jsonAdvantage : jsonArray)
    {
        auto oneAdvantageJsonObj = jsonAdvantage.toObject();

        OneAdvantageConfig oneAdvantage;
        oneAdvantage.title = oneAdvantageJsonObj["title"].toString();
        oneAdvantage.description = oneAdvantageJsonObj["description"].toString();
        oneAdvantage.descriptionMap = oneAdvantageJsonObj["descriptionmap"].toString();
        oneAdvantage.videoPath = oneAdvantageJsonObj["videoPath"].toString();
        advantagesConfig->advantages.push_back(oneAdvantage);
    }
}

void ConfigParser::parseComplexityConfig(QSharedPointer<ComplexityConfig> complexityConfig, const QJsonObject& jsonObject)
{
    complexityConfig->instruction = jsonObject["instruction"].toInt();
    complexityConfig->roulette = jsonObject["roulette"].toInt();

    auto gamesComplArray = jsonObject["game"].toArray();

    for(auto compl: gamesComplArray)
    {
        OneGameComplexityConfig complConfig;
        auto complObj = compl.toObject();
        complConfig.attentionMin = complObj["attentionMin"].toInt();
        complConfig.attentionMax = complObj["attentionMax"].toInt();

        complConfig.velocityMin = complObj["velocityMin"].toDouble();
        complConfig.velocityMax = complObj["velocityMax"].toDouble();
        complConfig.backMove = complObj["backMove"].toBool();

        complConfig.velocityBackMin = complObj["velocityBackMin"].toDouble();
        complConfig.velocityBackMax = complObj["velocityBackMax"].toDouble();

        complexityConfig->gameComplexities.push_back(complConfig);
    }
}
