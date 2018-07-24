#ifndef MINDWAVEPARSER_H
#define MINDWAVEPARSER_H

#include <QObject>
#include "config/Config.h"

struct MindwaveData
{
    MindwaveData()
    {

    }

    bool valid = false;
    int attention = 0;
    int meditation = 0;
    int poorSignalLevel = 0;
    QString poorSignalColor = "#999999";
};

class MindwaveParserBase : public QObject
{
    Q_OBJECT
public:
    explicit MindwaveParserBase(QObject *parent = nullptr);

    virtual void setConfig(const MindwaveConfig& value);
    virtual void parse(const QString& data);
    virtual void parse(const QByteArray& data);

    QString getPoorSignalColor(int value) const;

protected:
    MindwaveConfig mindwaveConfig;
    int remapPoorSignalLevel(int signalValue) const;

signals:
     void scanningInfo(int signalValue, const QString& status);
     void mindwaveDataParsed(const MindwaveData& data);

public slots:
    virtual void onDataRecieve(const QString& data);
    virtual void onDataRecieve(const QByteArray& data);

};

#endif // MINDWAVEPARSER_H
