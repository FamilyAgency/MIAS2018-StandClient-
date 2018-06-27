#ifndef ARDUINOCOMPONENT_H
#define ARDUINOCOMPONENT_H

#include <QObject>
#include <QTimer>

#include "config/Config.h"
#include "components/ExternalSystemComponent.h"
#include "arduino/ArduinoDataReader.h"

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

    Q_INVOKABLE QVariantList getPortsAvailable() const;
    Q_INVOKABLE void startReading(int modelIndex);

private:
     ArduinoConfig arduinoConfig;
     bool _connected = false;
     ArduinoDataReader* arduinoDataReader;

signals:
    void configChanged();
    void connectedChanged();

public slots:
    void onDataReaded(const QString&);
    void onReadError();
};

#endif // ARDUINOCOMPONENT_H
