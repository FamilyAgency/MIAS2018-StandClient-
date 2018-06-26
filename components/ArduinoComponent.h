#ifndef ARDUINOCOMPONENT_H
#define ARDUINOCOMPONENT_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>
#include "config/Config.h"
#include "components/ExternalSystemComponent.h"

class ArduinoComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(ArduinoConfig config READ config WRITE setConfig NOTIFY configChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit ArduinoComponent(QObject *parent = nullptr);

    void setConfig(const ArduinoConfig& config);
    ArduinoConfig config() const;

    virtual void start() override;
    virtual void setQmlContext(QQmlContext* value) override;
    virtual bool isHealthy() override;

    void setConnected(bool value);
    bool connected() const;

private:
     const int taskTimerMills = 1000;

     ArduinoConfig arduinoConfig;
     bool _connected = false;

     QSerialPort* serialPort = nullptr;
     QByteArray readData;
     QTimer* timer;

signals:
    void configChanged();
    void connectedChanged();

public slots:
    void onReadyRead();
    void onReadError(QSerialPort::SerialPortError error);
    void onUpdate();
};

#endif // ARDUINOCOMPONENT_H
