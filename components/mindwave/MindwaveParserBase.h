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
    virtual MindwaveData parse(const QString& data);

    QString getPoorSignalColor(int value) const;

protected:
    MindwaveConfig mindwaveConfig;
    virtual MindwaveData parseOneDataChunck(const QString& data);

signals:
    void notScanning();
};

#endif // MINDWAVEPARSER_H
