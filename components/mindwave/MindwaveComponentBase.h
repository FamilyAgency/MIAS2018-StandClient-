#ifndef MINDWAVECOMPONENT_H
#define MINDWAVECOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "MindwaveReaderBase.h"
#include "MindwaveParserBase.h"

class MindwaveComponentBase : public ExternalSystemComponent
{    
    Q_OBJECT

    Q_PROPERTY(MindwaveConfig mindwaveConfig READ mindwaveConfig WRITE setMindwaveConfig NOTIFY mindwaveConfigChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int attention READ attention WRITE setAttention NOTIFY attentionChanged)
    Q_PROPERTY(int meditation READ meditation WRITE setMeditation NOTIFY meditationChanged)
    Q_PROPERTY(int poorSignalLevel READ poorSignalLevel WRITE setPoorSignalLevel NOTIFY poorSignalLevelChanged)

public:
    explicit MindwaveComponentBase(QObject *parent = nullptr);
    virtual ~MindwaveComponentBase();

    enum class DeviceState
    {
        None,
        Scanning,
        NotScanning,
        Reading
    };
    Q_ENUMS(DeviceState)

    Q_INVOKABLE QString poorSignalColor() const;
    Q_INVOKABLE DeviceState getDeviceState() const;

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr value) override;
    virtual void start() override;
    virtual void stop() override;
    virtual bool isHealthy() override;

    MindwaveConfig mindwaveConfig() const;
    void setMindwaveConfig(const MindwaveConfig& );

    void setAttention(int value);
    int attention() const;

    void setMeditation(int value);
    int meditation() const;

    void setPoorSignalLevel(int value);
    int poorSignalLevel() const;

    void setConnected(bool value);
    bool connected() const;

    friend class MindwaveComponentTest;    

protected:
    MindwaveConfig _mindwaveConfig;
    QSharedPointer<MindwaveReaderBase> mindwaveReader;
    QSharedPointer<MindwaveParserBase> mindwaveParser;

    QTimer* timeoutTimer = nullptr;

    int _attention = 0;
    int _meditation = 0;
    int _poorSignalLevel = 0;
    bool _connected = false;
    QString _poorSignalColor = "black";

    void parse(const QString& data);

    void setDeviceState(DeviceState value);    

    DeviceState deviceState = DeviceState::None;

signals:
    void attentionChanged();
    void meditationChanged();
    void poorSignalLevelChanged();
    void mindwaveConfigChanged();
    void connectedChanged();

    void deviceStateChanged(DeviceState state);

private slots:
    virtual void onDataParsed(const MindwaveData& mindwaveData);
    virtual void onScanningInfo(int, const QString&);
    virtual void onTimeoutHandle();

    void onSignalLevelParsed(int value);
    void onMeditationParsed(int value);
    void onAttentionParsed(int value);

    void onConnectionSuccess();
    void onDisconnectionSuccess();
};

#endif // MINDWAVECOMPONENT_H
