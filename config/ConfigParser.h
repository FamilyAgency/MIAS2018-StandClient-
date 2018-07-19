#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QObject>
#include <QString>
#include "Config.h"

class ConfigParser : public QObject
{
    Q_OBJECT

public:
    ConfigParser();
    virtual ~ConfigParser();

signals:
    void parseComplete(ConfigPtr);
    void parseError(const QString& errorMessage);

public slots:
    void parse(const QString& configData);

private:
    ConfigPtr config;
    bool wasParsingError = false;
    void parseMainConfig(QSharedPointer<MainConfig> mainConfig, const QJsonObject& jsonObj);
    void parseRFIDConfig(QSharedPointer<RFIDConfig> rfidConfig, const QJsonObject& jsonObj);
    void parseMindwaveConfig(QSharedPointer<MindwaveConfig> mindwaveConfig, const QJsonObject& jsonObj);
    void parseServerConfig(QSharedPointer<ServerConfig> serverConfig, const QJsonObject& jsonObj);
    void parseSlackConfig(QSharedPointer<SlackFullConfig> slackConfig,  const QJsonArray& jsonArray);
    void parseLoggerConfig(QSharedPointer<LoggerConfig> loggerConfig, const QJsonObject& jsonObj);
    void parseMonitoringConfig(QSharedPointer<MonitoringConfig> monitoringConfig, const QJsonObject& jsonObj);
    void parseStandGamesConfig(QSharedPointer<StandGamesConfig> standGamesConfig, const QJsonArray& jsonArray);
};

#endif // CONFIGPARSER_H
