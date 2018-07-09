#ifndef RFIDCOMPONENT_H
#define RFIDCOMPONENT_H

#include <QObject>
#include <QTimer>

#include "config/Config.h"
#include "components/ExternalSystemComponent.h"
#include "rfid/UHFJsonDataReader.h"

class RFIDComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(RFIDConfig rfidConfig READ rfidConfig WRITE setRfidConfig NOTIFY rfidConfigChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit RFIDComponent(QObject *parent = nullptr);
    virtual ~RFIDComponent();

    Q_INVOKABLE QVariantList getPortsAvailable() const;
    Q_INVOKABLE void startReading(int modelIndex);

    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setQmlContext(QQmlContext* value) override;
    virtual bool isHealthy() override;

    void setRfidConfig(const RFIDConfig& rfidConfig);
    RFIDConfig rfidConfig() const;

    void setConnected(bool value);
    bool connected() const;

private:
     RFIDConfig _rfidConfig;
     bool _connected = false;
     QSharedPointer<BaseRFIDDataReader> rfidDataReader;

signals:
    void rfidConfigChanged();
    void connectedChanged();
    void onRFIDRecieve(int id);

public slots:
    void onDataReaded(const QString&);
    void onReadError();
};

#endif // RFIDCOMPONENT_H
