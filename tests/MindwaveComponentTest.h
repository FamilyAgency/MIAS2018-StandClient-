#ifndef MINDWAVECOMPONENTTEST_H
#define MINDWAVECOMPONENTTEST_H

#include <QObject>
#include "components/MindwaveComponent.h"

class MindwaveComponentTest : public MindwaveComponent
{
    Q_OBJECT
public:
    explicit MindwaveComponentTest(QObject *parent = nullptr);
    virtual void setConfig(const MindwaveConfig& config) override;

private:
    QTimer* timer;
    const int taskTimerMills = 1000;

signals:

private slots:
    void simulateMindwaveRead();
};

#endif // MINDWAVECOMPONENTTEST_H
