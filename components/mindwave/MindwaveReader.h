#ifndef MINDWAVEREADER_H
#define MINDWAVEREADER_H

#include <QObject>
#include "core/Types.h"
#include "network/socketClient/TCPSocketClient.h"

class MindwaveReader : public QObject
{
    Q_OBJECT
public:
    explicit MindwaveReader(QObject *parent = nullptr);

    virtual void setConfig(const MindwaveConfig& value);
    virtual void start();

private:
    MindwaveConfig mindwaveConfig;
    void setConnected(bool value);

    bool _connected = false;
    QScopedPointer<TCPSocketClient> client;

signals:
    void connectionSuccess();
    void disconnectionSuccess();
    void dataRecieve(const QString&);

private slots:
    void onItemDataRecieve(const QString& data);
    void onConnectionSuccess();
    void onDisconnectionSuccess();
};

#endif // MINDWAVEREADER_H
