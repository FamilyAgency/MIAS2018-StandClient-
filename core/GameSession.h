#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QObject>
#include <QTimer>
#include <QQmlContext>

class GameSession : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(float sessionTime READ sessionTime WRITE setSessionTime NOTIFY sessionTimeChanged)
    Q_PROPERTY(float cleanTime READ cleanTime WRITE setCleanTime NOTIFY cleanTimeChanged)

    explicit GameSession(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    void start();
    void stop();

    void addTaskTime(float time);
    float sessionTime() const;
    float cleanTime() const;

    void setSessionTime(float value);
    void setCleanTime(float value);

    const int sessionTimerMills = 10;
    const float toSeconds = 1/1000.0f;

private:
    float _sessionTime = 0.0;
    float _cleanTime = 0.0;
    int sessionStartTime, gameCleanTime;
    QTimer* sessionTimer;

signals:
    void sessionTimeChanged();
    void cleanTimeChanged();

public slots:
    void onSessionTimerUpdate();
};

#endif // GAMESESSION_H
