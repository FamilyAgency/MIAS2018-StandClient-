#ifndef RFIDCOMPONENT_H
#define RFIDCOMPONENT_H

#include <QObject>
#include <QTimer>

#include "config/Config.h"
#include "components/ExternalSystemComponent.h"
#include "rfid/BaseRFIDDataReader.h"
#include "rfid/UHFDataReader.h"

class RFIDComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(RFIDConfig config READ config WRITE setConfig NOTIFY configChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit RFIDComponent(QObject *parent = nullptr);

    void setConfig(const RFIDConfig& config);
    RFIDConfig config() const;

    virtual void start() override;
    virtual void setQmlContext(QQmlContext* value) override;
    virtual bool isHealthy() override;

    void setConnected(bool value);
    bool connected() const;

    Q_INVOKABLE QVariantList getPortsAvailable() const;
    Q_INVOKABLE void startReading(int modelIndex);

private:
     RFIDConfig rfidConfig;
     bool _connected = false;
     BaseRFIDDataReader* rfidDataReader;

signals:
    void configChanged();
    void connectedChanged();

public slots:
    void onDataReaded(const QString&);
    void onReadError();
};

#endif // RFIDCOMPONENT_H
