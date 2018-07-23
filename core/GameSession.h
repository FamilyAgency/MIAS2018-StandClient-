#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QObject>
#include <QTimer>
#include <QQmlContext>

class GameSession : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float sessionTime READ sessionTime WRITE setSessionTime NOTIFY sessionTimeChanged) 
public:
    explicit GameSession(QObject *parent = nullptr);
    virtual ~GameSession();

    const int sessionTimerMills = 10;
    const float toSeconds = 1/1000.0f;

    virtual void start();
    virtual void stop();
    virtual void setQmlContext(QQmlContext* value);

    float sessionTime() const;
    void setSessionTime(float value);

private:
    float _sessionTime = 0.0;
    int sessionStartTime;
    QTimer* sessionTimer;

signals:
    void sessionTimeChanged();

public slots:
    void onSessionTimerUpdate();
};

#endif // GAMESESSION_H
