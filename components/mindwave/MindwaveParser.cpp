#include "MindwaveParser.h"
#include "tools/MathTools.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>

MindwaveParser::MindwaveParser(QObject *parent) : QObject(parent)
{

}

void MindwaveParser::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
}

MindwaveData MindwaveParser::parse(const QString& data)
{
    MindwaveData mindwaveData;
    auto delimeter = mindwaveConfig.delimeter;

    QStringList json = data.split(delimeter);
    int count = 0;

    for(int i = 0; i < json.length(); i++)
    {
        if(json[i].indexOf("eSense") != -1)
        {
            count++;
            mindwaveData = parseOneDataChunck(json[i]);
            break;
        }
    }

    return mindwaveData;
}

MindwaveData MindwaveParser::parseOneDataChunck(const QString& data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    QJsonObject eSenseJson = jsonObj.value("eSense").toObject();
    MindwaveData mindwaveData;

    mindwaveData.attention = eSenseJson.value("attention").toInt();
    mindwaveData.meditation = eSenseJson.value("meditation").toInt();

    int signalValue = jsonObj.value("poorSignalLevel").toInt();
    mindwaveData.poorSignalLevel = MathTools::map<float>(signalValue, 0,  200, 100,  0);

    mindwaveData.poorSignalColor = getPoorSignalColor(signalValue);
    mindwaveData.valid = true;
    return mindwaveData;
}

QString MindwaveParser::getPoorSignalColor(int value) const
{
    QString color = "#999999";

    if(value >= 66 && value <= 100)
    {
        color = "#009900";
    }
    else if(value >= 30 && value <= 66)
    {
        color = "#999900";
    }
    else if(value >= 0 && value <= 30)
    {
        color = "#999999";
    }

    return color;
}
