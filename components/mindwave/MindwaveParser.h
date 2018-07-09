#ifndef MINDWAVEPARSER_H
#define MINDWAVEPARSER_H

#include <QObject>
#include "core/Types.h"

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

class MindwaveParser : public QObject
{
    Q_OBJECT
public:
    explicit MindwaveParser(QObject *parent = nullptr);

    virtual void setConfig(const MindwaveConfig& value);
    virtual MindwaveData parse(const QString& data);

private:
     MindwaveConfig mindwaveConfig;

     QString getPoorSignalColor(int value) const;
     MindwaveData parseOneDataChunck(const QString& data);

};

#endif // MINDWAVEPARSER_H
