#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>


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
};
Q_DECLARE_METATYPE(MindwaveConfig)


struct RFIDConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString serialPort MEMBER serialPort)
    Q_PROPERTY(int baudRate MEMBER baudRate)
    Q_PROPERTY(bool autoConnect MEMBER autoConnect)

public:
    QString serialPort = "COM1";
    QString portKeyWord = "Arduino";
    int baudRate = 9600;
    bool useKeyword = true;
    bool autoConnect = true;
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
    Q_PROPERTY(QRect gameScreen MEMBER gameScreen)

 public:
    int version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    int appId;
    QString workingDirectory;
    QString folderSeparator = "\\";
    QString appName = "None";
    QRect touchScreen;
    QRect gameScreen;
};
Q_DECLARE_METATYPE(MainConfig)


struct ServerConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString url MEMBER url)

public:
    QString url = "http://mindwave.family.creative";
};
Q_DECLARE_METATYPE(ServerConfig)

struct SlackConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString logChannel MEMBER logChannel)
    Q_PROPERTY(QString errorChannel MEMBER errorChannel)
    Q_PROPERTY(bool enabled MEMBER enabled)

public:
    QString logChannel = "";
    QString errorChannel = "";
    bool enabled = false;
};
Q_DECLARE_METATYPE(SlackConfig)


#endif // TYPES_H
