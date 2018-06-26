#ifndef PRETASK_H
#define PRETASK_H

#include <QObject>
#include <QTimer>

class GamePreTask : public QObject
{
    Q_OBJECT
public:
    explicit GamePreTask(QObject *parent = nullptr);
    void init();
    void run();
    void stop();

signals:
    void update(float time);
    void complete();

private slots:
     void onUpdate();
private:
    QTimer* timer;
    int startTime = 0;
    const int preTaskMills = 3 * 1000;
    const int preTaskTimerMills = 10;
    const float toSeconds = 1/1000.0;
};

#endif // PRETASK_H
