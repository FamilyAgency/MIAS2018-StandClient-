#ifndef MINDWAVECOMPONENT_H
#define MINDWAVECOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "mindwave/MindwaveReader.h"
#include "mindwave/MindwaveParser.h"

class MindwaveComponent : public ExternalSystemComponent
{    
    Q_OBJECT

    Q_PROPERTY(MindwaveConfig config READ config WRITE setConfig NOTIFY configChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit MindwaveComponent(QObject *parent = nullptr);

    Q_PROPERTY(int attention READ attention WRITE setAttention NOTIFY attentionChanged)
    Q_PROPERTY(int meditation READ meditation WRITE setMeditation NOTIFY meditationChanged)
    Q_PROPERTY(int poorSignalLevel READ poorSignalLevel WRITE setPoorSignalLevel NOTIFY poorSignalLevelChanged)

    Q_INVOKABLE QString poorSignalColor() const;

    void setAttention(int value);
    int attention() const;

    void setMeditation(int value);
    int meditation() const;

    void setPoorSignalLevel(int value);
    int poorSignalLevel() const;

    void setConnected(bool value);
    bool connected() const;

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(const MindwaveConfig& value);
    virtual void start() override;
    MindwaveConfig config() const;
    virtual bool isHealthy() override;

    friend class MindwaveComponentTest;    

private:
    MindwaveConfig mindwaveConfig;
    MindwaveReader* mindwaveReader;
    MindwaveParser* mindwaveParser;

    int _attention = 0;
    int _meditation = 0;
    int _poorSignalLevel = 0;
    bool _connected = false;
    QString _poorSignalColor = "black";

    void parse(const QString& data);

signals:
    void attentionChanged();
    void meditationChanged();
    void poorSignalLevelChanged();
    void configChanged();
    void connectedChanged();

private slots:
    void onDataRecieve(const QString& data);
    void onConnectionSuccess();
    void onDisconnectionSuccess();
};

#endif // MINDWAVECOMPONENT_H
