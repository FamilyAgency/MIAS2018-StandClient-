#ifndef CONFIG_H
#define CONFIG_H

#include <QVector.h>
#include <QString.h>
#include <QStringList.h>
#include <QObject.h>
#include <QDebug.h>
#include <core/Types.h>

class Config
{
public:
    Config();
    bool valid = true;

    MainConfig configData;
    MindwaveConfig mindwaveConfig;

    QString getRawData() const;
    void setRawData(const QString& value);

private:
    QString rawData;
};

#endif // CONFIG_H
