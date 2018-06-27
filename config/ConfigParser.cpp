#include "ConfigParser.h"
#include "ConfigLoader.h"
#include "Config.h"

#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug.h>

ConfigParser::ConfigParser()
{
    config = new Config();
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

        config->configData   = parseConfigData(jsonObj);
        config->arduinoData  = parseArduinoData(jsonObj["arduino"].toObject());
        config->mindwaveData = parseMindwaveData(jsonObj["mindwave"].toObject());
        config->serverData   = parseServerData(jsonObj["server"].toObject());

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

MainConfig ConfigParser::parseConfigData(const QJsonObject& jsonObj)
{
    MainConfig configData;
    configData.version = jsonObj["version"].toString();
    configData.configUpdateUrl = jsonObj["configUpdateUrl"].toString();
    configData.needRemoteUpdate = jsonObj["needRemoteUpdate"].toBool();
    configData.standId = jsonObj["standId"].toInt();
    configData.appTypeId = jsonObj["appTypeId"].toInt();
    return configData;
}

ArduinoConfig ConfigParser::parseArduinoData(const QJsonObject& jsonObj)
{
    ArduinoConfig arduino;
    arduino.serialPort = jsonObj["serialPort"].toString();
    arduino.baudRate = jsonObj["baudRate"].toInt();
    arduino.autoConnect = jsonObj["autoConnect"].toBool();
    return arduino;
}

MindwaveConfig ConfigParser::parseMindwaveData(const QJsonObject& jsonObj)
{
    MindwaveConfig mindwave;
    mindwave.ip = jsonObj["ip"].toString();
    mindwave.port = jsonObj["port"].toInt();
    mindwave.autoConnect = jsonObj["autoConnect"].toBool();
    mindwave.delimeter = jsonObj["delimeter"].toString();
    mindwave.initialCommand = jsonObj["initialCommand"].toString();
    mindwave.authCommand = jsonObj["authCommand"].toString();
    return mindwave;
}

ServerConfig ConfigParser::parseServerData(const QJsonObject& jsonObj)
{
    ServerConfig server;
    server.url = jsonObj["url"].toString();
    return server;
}
