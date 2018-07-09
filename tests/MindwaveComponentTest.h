#ifndef MINDWAVECOMPONENTTEST_H
#define MINDWAVECOMPONENTTEST_H

#include <QObject>
#include "components/MindwaveComponent.h"

class MindwaveComponentTest : public MindwaveComponent
{
    Q_OBJECT
public:
    explicit MindwaveComponentTest(QObject *parent = nullptr);
    virtual void start() override;
    virtual void stop() override;

private:
    QTimer* timer;
    const int taskTimerMills = 1000;

private slots:
    void simulateMindwaveRead();
};

#endif // MINDWAVECOMPONENTTEST_H
