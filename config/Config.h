#ifndef CONFIG_H
#define CONFIG_H

#include <QVector.h>
#include <QString.h>
#include <QStringList.h>
#include <QObject.h>
#include <QDebug.h>
#include <core/Types.h>


typedef  QSharedPointer<class Config> ConfigPtr;

struct LoggerConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString localPath MEMBER localPath)
    Q_PROPERTY(bool localEnabled MEMBER localEnabled)

public:
    QString localPath = "logs";
    bool localEnabled = false;
};
Q_DECLARE_METATYPE(LoggerConfig)

class Config
{
public:
    Config();
    virtual ~Config();
    bool valid = true;

    QSharedPointer<MainConfig> mainConfig;
    QSharedPointer<MindwaveConfig> mindwaveConfig;
    QSharedPointer<RFIDConfig> rfidConfig;
    QSharedPointer<ServerConfig> serverConfig;
    QSharedPointer<SlackConfig> slackConfig;
    QSharedPointer<LoggerConfig> loggerConfig;

    QString getRawData() const;
    void setRawData(const QString& value);

private:
    QString rawData;
};

#endif // CONFIG_H
