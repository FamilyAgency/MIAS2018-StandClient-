#ifndef MINDWAVEPARSER_H
#define MINDWAVEPARSER_H

#include <QObject>
#include "core/Types.h"

struct MindwaveData
{
    MindwaveData()
    {

    }

    int attention;
    int meditation;
    int poorSignalLevel;
    QString poorSignalColor;
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
