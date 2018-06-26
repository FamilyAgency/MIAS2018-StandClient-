#ifndef MINDWAVECOMPONENT_H
#define MINDWAVECOMPONENT_H

#include <QObject>
#include "network/socketClient/TCPSocketClient.h"

class MindwaveComponent : public QObject
{    
    Q_OBJECT

    Q_PROPERTY(MindwaveConfig config READ config)

public:
    explicit MindwaveComponent(QObject *parent = nullptr);

    Q_PROPERTY(int attention READ attention WRITE setAttention NOTIFY attentionChanged)
    Q_PROPERTY(int meditation READ meditation WRITE setMeditation NOTIFY meditationChanged)
    Q_PROPERTY(int poorSignalLevel READ poorSignalLevel WRITE setPoorSignalLevel NOTIFY poorSignalLevelChanged)

    Q_INVOKABLE QString poorSignalColor() const;
    Q_INVOKABLE int getMeditationDelta() const;
    Q_INVOKABLE int getAttentionDelta() const;

     int attention() const;
     int meditation() const;
     int poorSignalLevel() const;

     void setAttention(int value);
     void setMeditation(int value);
     void setPoorSignalLevel(int value);

     void parse(const QString& data);
     void setConfig(const MindwaveConfig& config);   

     MindwaveConfig config() const
     {
         return mindwaveConfig;
     }

private:
     MindwaveConfig mindwaveConfig;

     int _attention = 0;
     int _meditation = 0;

     int _lastAttention = 0;
     int _lastMeditation = 0;

     int _poorSignalLevel = 0;

     QString _poorSignalColor = "black";


     QScopedPointer<TCPSocketClient> client;
     QTimer* senderTimer;

signals:
     void attentionChanged();
     void meditationChanged();
     void poorSignalLevelChanged();

private slots:
     void onItemDataRecieve(const QString& data);
     void onConnectionSuccess();
     void onDisconnectionSuccess();


     void senderTimerHandler();

};

#endif // MINDWAVECOMPONENT_H
