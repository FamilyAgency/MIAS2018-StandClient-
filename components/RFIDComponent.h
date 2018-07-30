#ifndef RFIDCOMPONENT_H
#define RFIDCOMPONENT_H

#include <QObject>
#include <QTimer>

#include "config/Config.h"
#include "components/ExternalSystemComponent.h"

class RFIDComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(RFIDConfig rfidConfig READ rfidConfig WRITE setRfidConfig NOTIFY rfidConfigChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit RFIDComponent(QObject *parent = nullptr);
    virtual ~RFIDComponent();

    enum class CardReaderState
    {
        Reading,
        Writing,
        Stopped,
        Validating
    };
    Q_ENUMS(CardReaderState)

    Q_INVOKABLE virtual void startReading();
    Q_INVOKABLE virtual void startWriting(const QString& data);
    Q_INVOKABLE virtual void stopAll();

    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setQmlContext(QQmlContext* value) override;
    virtual bool isHealthy() override;

    void setRfidConfig(const RFIDConfig& rfidConfig);
    RFIDConfig rfidConfig() const;

    void setConnected(bool value);
    bool connected() const;

protected:
    CardReaderState cardReaderState;
    RFIDConfig _rfidConfig;
    bool _connected = false;

    void setCardReaderState(CardReaderState state);

signals:
    void rfidConfigChanged();
    void connectedChanged();
    void onRFIDRecieve(int id);
    void cardReaderStateChanged(CardReaderState state);
};

#endif // RFIDCOMPONENT_H
