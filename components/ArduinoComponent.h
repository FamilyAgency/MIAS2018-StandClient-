#ifndef ARDUINOCOMPONENT_H
#define ARDUINOCOMPONENT_H

#include <QObject>
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

    virtual void setQmlContext(QQmlContext* value) override;

    void setConnected(bool value);
    bool connected() const;

    virtual bool isHealthy() override;

private:
     ArduinoConfig arduinoConfig;
     bool _connected = false;

signals:
    void configChanged();
    void connectedChanged();

public slots:
};

#endif // ARDUINOCOMPONENT_H
