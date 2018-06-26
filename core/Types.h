#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>

typedef int StandId;


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
    QString autchCommand = "{\"appName\":\"BrainwaveShooters\",\"appKey\":\"0054141b4b4c567c558d3a76cb8d715cbde03096\"}\\r";
};
Q_DECLARE_METATYPE(MindwaveConfig)


struct ArduinoConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString serialPort MEMBER serialPort)
    Q_PROPERTY(int baudRate MEMBER baudRate)

public:
    QString serialPort = "COM1";
    int baudRate = 9600;
};
Q_DECLARE_METATYPE(ArduinoConfig)

struct MainConfig
{
    QString version;
    QString configUpdateUrl;
    bool needRemoteUpdate;
    StandId standId;
};

struct ServerConfig
{
private:
    Q_GADGET
    Q_PROPERTY(QString url MEMBER url)

public:
    QString url = "http://mindwave.family.creative";
};
Q_DECLARE_METATYPE(ServerConfig)


#endif // TYPES_H
