#ifndef PRETASK_H
#define PRETASK_H

#include <QObject>
#include <QTimer>

class GameCountDown : public QObject
{
    Q_OBJECT
public:
    explicit GameCountDown();
    ~GameCountDown();

    void init();
    void run();
    void stop();

signals:
    void update(float time);
    void complete();

private slots:
     void onUpdate();

private:
    QTimer* timer = nullptr;
    int startTime = 0;
    const int preTaskMills = 3 * 1000;
    const int preTaskTimerMills = 10;
    const float toSeconds = 1/1000.0f;
};

#endif // PRETASK_H
