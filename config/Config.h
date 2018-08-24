#ifndef CONFIG_H
#define CONFIG_H

#include <QVector.h>
#include <QString.h>
#include <QStringList.h>
#include <QObject.h>
#include <QDebug.h>
#include <QRect.h>
#include <core/Types.h>

typedef  QSharedPointer<class Config> ConfigPtr;

struct TCPConfig
{
    QString ip = "127.0.0.1";
    int port = 13854;
    bool autoConnect = true;
    QString delimeter = "\r";
};

struct MindwaveConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString ip MEMBER ip)
    Q_PROPERTY(int port MEMBER port)
    Q_PROPERTY(bool autoConnect MEMBER autoConnect)
    Q_PROPERTY(QString delimeter MEMBER delimeter)

public:
    TCPConfig getTCPConfig()
    {
        TCPConfig config;
        config.ip = ip;
        config.port = port;
        config.autoConnect = autoConnect;
        config.delimeter = delimeter;
        return config;
    }

    QString ip = "127.0.0.1";
    int port = 13854;
    bool autoConnect = true;
    QString delimeter = "\r";
    QString initialCommand = "{\"enableRawOutput\": true, \"format\": \"Json\"}\\r";
    QString authCommand = "{\"appName\":\"BrainwaveShooters\",\"appKey\":\"0054141b4b4c567c558d3a76cb8d715cbde03096\"}\\r";
    QString type = "serial";
    int timeoutMills = 2000;
    QString com = "COM6";

};
Q_DECLARE_METATYPE(MindwaveConfig)


struct RFIDConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString serialPort MEMBER serialPort)
    Q_PROPERTY(int baudRate MEMBER baudRate)
    Q_PROPERTY(bool autoConnect MEMBER autoConnect)
    Q_PROPERTY(QString writeValidation MEMBER writeValidation)
    Q_PROPERTY(bool beepEnabled MEMBER beepEnabled)

public:
    QString serialPort = "COM1";
    QString portKeyWord = "Arduino";
    int baudRate = 9600;
    bool useKeyword = true;
    bool autoConnect = true;
    QString type;
    QString writeValidation = "none";
    bool beepEnabled = false;
};
Q_DECLARE_METATYPE(RFIDConfig)

struct MainConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int version MEMBER version)
    Q_PROPERTY(QString configUpdateUrl MEMBER configUpdateUrl)
    Q_PROPERTY(bool needRemoteUpdate MEMBER needRemoteUpdate)
    Q_PROPERTY(int appId MEMBER appId)
    Q_PROPERTY(QString workingDirectory MEMBER workingDirectory)
    Q_PROPERTY(QString folderSeparator MEMBER folderSeparator)
    Q_PROPERTY(QString appName MEMBER appName)
    Q_PROPERTY(QRect touchScreen MEMBER touchScreen)
    Q_PROPERTY(bool touchScreenIsSplash MEMBER touchScreenIsSplash)
    Q_PROPERTY(QRect gameScreen MEMBER gameScreen)
    Q_PROPERTY(bool gameScreenIsSplash MEMBER gameScreenIsSplash)
    Q_PROPERTY(QString qmlOnStart MEMBER qmlOnStart)
    Q_PROPERTY(bool release MEMBER release)


 public:
    int version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int appId;
    QString workingDirectory;
    QString folderSeparator = "\\";
    QString appName = "None";
    QRect touchScreen;
    bool touchScreenIsSplash;
    QRect gameScreen;
    bool gameScreenIsSplash;
    QString qmlOnStart = "qrc:/qml/mainRelease.qml";
    bool release = false;
    QString videoEXT = "mp4";
};
Q_DECLARE_METATYPE(MainConfig)


struct ServerAPI
{
private:
    Q_GADGET
    Q_PROPERTY(QString testUser MEMBER testUser)
    Q_PROPERTY(bool pinNeed MEMBER pinNeed)


public:
    QString testUser = 0;
    bool pinNeed = true;
};
Q_DECLARE_METATYPE(ServerAPI)

struct ServerConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString url MEMBER url)
    Q_PROPERTY(int requestTimemoutInterval MEMBER requestTimemoutInterval)
    Q_PROPERTY(int requestTryCount MEMBER requestTryCount)

public:
    QString url = "http://mindwave.family.creative";
    int requestTimemoutInterval = 5000;
    int requestTryCount = 2;
    ServerAPI serverAPI;
};
Q_DECLARE_METATYPE(ServerConfig)

struct SlackAppConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString logChannel MEMBER logChannel)
    Q_PROPERTY(QString errorChannel MEMBER errorChannel)
    Q_PROPERTY(bool enabled MEMBER enabled)
    Q_PROPERTY(int appId MEMBER appId)

public:
    QString logChannel = "";
    QString errorChannel = "";
    bool enabled = false;
    int appId = 0;
};
Q_DECLARE_METATYPE(SlackAppConfig)


struct SlackFullConfig
{
    QMap<int, SlackAppConfig> slackMap;
};

struct MonitoringConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int memoryCheckMills MEMBER memoryCheckMills)
    Q_PROPERTY(bool enabled MEMBER enabled)

public:
    int memoryCheckMills = 10000;
    bool enabled = false;
};
Q_DECLARE_METATYPE(MonitoringConfig)

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

struct OneAdvantageConfig
{
    QString title = "title";
    QString description = "description";
    QString descriptionMap = "descriptionMap";
    QString videoPath = "";
};

struct OneStageConfig
{
    QVector<QPointF> path;
};

struct StandOneGameConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString category MEMBER category)
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(QString descriptionWin MEMBER descriptionWin)
    Q_PROPERTY(QString imageWinName MEMBER imageWinName)
    Q_PROPERTY(QString iconName MEMBER iconName)

public:
    QString category = "category";
    QString description = "description";
    QString descriptionWin = "descriptionWin";
    QString imageWinName = "imageWinName";
    QString iconName = "iconName";

    QVector<OneStageConfig> stages;
    QVector<QPointF> startPath;
    QVector<QPointF> finalPath;

};
Q_DECLARE_METATYPE(StandOneGameConfig)

struct StandOneAnimConfig
{
private:
    Q_GADGET
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)
    Q_PROPERTY(QString path MEMBER path)
    Q_PROPERTY(int frames MEMBER frames)

public:
    int x = 0;
    int y = 0;
    QString path = "";
    int frames = 0;

};
Q_DECLARE_METATYPE(StandOneAnimConfig)



struct SuperGameConfig
{
    int time;
    QVector<QPointF> path;
};

struct StandGamesConfig
{
    QVector<StandOneGameConfig> games;
    SuperGameConfig superGame;
};

struct StandAnimConfig
{
     QVector<StandOneAnimConfig> animations;
};

struct AdvantagesConfig
{
     QVector<OneAdvantageConfig> advantages;
};

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
    QSharedPointer<SlackFullConfig> slackConfig;
    QSharedPointer<LoggerConfig> loggerConfig;
    QSharedPointer<MonitoringConfig> monitoringConfig;
    QSharedPointer<StandGamesConfig> standGamesConfig;
    QSharedPointer<StandAnimConfig> standAnimConfig;
    QSharedPointer<AdvantagesConfig> advantagesConfig;

    QString getRawData() const;
    void setRawData(const QString& value);

private:
    QString rawData;
};

#endif // CONFIG_H
