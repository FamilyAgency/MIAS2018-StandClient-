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
        //qDebug()<<"configData................"<<endl;
       // qDebug()<<configData <<endl;
       // qDebug()<<"configData................"<<endl;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configData.toUtf8());
        QJsonObject jsonObj   = jsonDoc.object();

        config->configData = parseConfigData(jsonObj);
        //config->processData = parseProcessesData(jsonObj);
       // config->socketServerData = parseSocketServerData(jsonObj);
       // config->socketClientData = parseSocketClientData(jsonObj);
      // config->monitoringData = parseMonitoringData(jsonObj);
       // config->autoUpdateData = parseAutoUpdateData(jsonObj);
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
    configData.standId = jsonObj["launcherId"].toInt();
    return configData;
}
