#include "MindwaveComponentTest.h"
#include "tools/MathTools.h"

MindwaveComponentTest::MindwaveComponentTest(QObject *parent) : MindwaveComponent(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(simulateMindwaveRead()));
}

void MindwaveComponentTest::setConfig(const MindwaveConfig& config)
{
    //TODO
    mindwaveConfig = config;
    client->setConfig(mindwaveConfig.getTCPConfig());
    timer->start(taskTimerMills);
    emit configChanged();
}

void MindwaveComponentTest::simulateMindwaveRead()
{
    _lastAttention = _attention;
    _lastMeditation = _meditation;

    int min = 50;
    int max = 100;
    int RandAtten = qrand() % ((max + 1) - min) + min;
    setAttention(RandAtten);

    int  RandMed = qrand() % ((100 + 1) - 0) + 0;
    setMeditation(RandMed);

    int signalValue = 0;
    int signalRemappedValue = MathTools::map<float>(signalValue, 0,  200, 100,  0);

    setPoorSignalLevel(signalRemappedValue);

    qDebug()<<"attention: "<<_attention <<"meditation: "<<_meditation <<"poorSignalLevel: "<<_poorSignalLevel;
}
