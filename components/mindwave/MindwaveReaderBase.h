#ifndef MINDWAVEREADER_H
#define MINDWAVEREADER_H

#include <QObject>
#include "core/Types.h"
#include "network/socketClient/TCPSocketClient.h"

class MindwaveReaderBase : public QObject
{
    Q_OBJECT
public:
    explicit MindwaveReaderBase(QObject *parent = nullptr);
    virtual ~MindwaveReaderBase();

    virtual void setConfig(const MindwaveConfig& value);
    virtual void start();

protected:
    MindwaveConfig mindwaveConfig;
    void setConnected(bool value);

    bool _connected = false;
    QScopedPointer<TCPSocketClient> client;

signals:
    void connectionSuccess();
    void disconnectionSuccess();
    void dataRecieve(const QString&);

protected slots:
    virtual void onConnectionSuccess();
    void onItemDataRecieve(const QString& data);
    void onDisconnectionSuccess();
};

#endif // MINDWAVEREADER_H
