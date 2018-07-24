#ifndef MINDWAVECOMPONENTTEST_H
#define MINDWAVECOMPONENTTEST_H

#include <QObject>
#include "components/mindwave/MindwaveComponentBase.h"

class MindwaveComponentTest : public MindwaveComponentBase
{
    Q_OBJECT
public:
    explicit MindwaveComponentTest(QObject *parent = nullptr);
    virtual ~MindwaveComponentTest();

    virtual void start() override;
    virtual void stop() override;
    virtual void setConfig(ConfigPtr value) override;


private:
    QTimer* timer;
    const int taskTimerMills = 1000;

private slots:
    void simulateMindwaveRead();
};

#endif // MINDWAVECOMPONENTTEST_H
