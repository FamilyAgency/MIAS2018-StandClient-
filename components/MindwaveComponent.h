#ifndef MINDWAVECOMPONENT_H
#define MINDWAVECOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "mindwave/MindwaveReader.h"
#include "mindwave/MindwaveParser.h"

class MindwaveComponent : public ExternalSystemComponent
{    
    Q_OBJECT

    Q_PROPERTY(MindwaveConfig mindwaveConfig READ mindwaveConfig WRITE setMindwaveConfig NOTIFY mindwaveConfigChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int attention READ attention WRITE setAttention NOTIFY attentionChanged)
    Q_PROPERTY(int meditation READ meditation WRITE setMeditation NOTIFY meditationChanged)
    Q_PROPERTY(int poorSignalLevel READ poorSignalLevel WRITE setPoorSignalLevel NOTIFY poorSignalLevelChanged)

public:
    explicit MindwaveComponent(QObject *parent = nullptr);
    virtual ~MindwaveComponent();

    Q_INVOKABLE QString poorSignalColor() const;

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

private:
    MindwaveConfig _mindwaveConfig;
    QSharedPointer<MindwaveReader> mindwaveReader;
    QSharedPointer<MindwaveParser> mindwaveParser;

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
    void mindwaveConfigChanged();
    void connectedChanged();

private slots:
    void onDataRecieve(const QString& data);
    void onConnectionSuccess();
    void onDisconnectionSuccess();
};

#endif // MINDWAVECOMPONENT_H
