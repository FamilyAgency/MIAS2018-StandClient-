#include "MindwaveParserTCP.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>

MindwaveParserTCP::MindwaveParserTCP(QObject *parent) : MindwaveParserBase(parent)
{

}

void MindwaveParserTCP::parse(const QString& data)
{
    qDebug()<<"income data"<<data;

    MindwaveData mindwaveData;
    auto delimeter = mindwaveConfig.delimeter;

    QStringList json = data.split(delimeter);
    int count = 0;

    for(int i = 0; i < json.length(); i++)
    {
        if(json[i].indexOf("eSense") != -1)
        {
            count++;
            // qDebug()<<json[i];
            mindwaveData = parseOneDataChunck(json[i]);
            break;
        }
    }

    if(!mindwaveData.valid)
    {
        if(json.length() > 0)
        {
            // qDebug()<<"inside   "<<json[0];
            QJsonDocument jsonDoc = QJsonDocument::fromJson(json[0].toUtf8());
            QJsonObject jsonObj   = jsonDoc.object();

            int signalValue = jsonObj.value("poorSignalLevel").toInt();
            mindwaveData.poorSignalLevel = remapPoorSignalLevel(signalValue);

            QString status = jsonObj.value("status").toString();
            emit scanningInfo(mindwaveData.poorSignalLevel, status);
        }
    }

    emit mindwaveDataParsed(mindwaveData);
}

MindwaveData MindwaveParserTCP::parseOneDataChunck(const QString& data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    QJsonObject eSenseJson = jsonObj.value("eSense").toObject();
    MindwaveData mindwaveData;

    mindwaveData.attention = eSenseJson.value("attention").toInt();
    mindwaveData.meditation = eSenseJson.value("meditation").toInt();

    int signalValue = jsonObj.value("poorSignalLevel").toInt();
    mindwaveData.poorSignalLevel = remapPoorSignalLevel(signalValue);

    mindwaveData.poorSignalColor = getPoorSignalColor(signalValue);
    mindwaveData.valid = true;
    return mindwaveData;
}
