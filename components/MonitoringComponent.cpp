#include "MonitoringComponent.h"

MonitoringComponent::MonitoringComponent(QObject *parent) : BaseComponent(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    loggerComponent.reset(new LoggerComponent());
}

MonitoringComponent::~MonitoringComponent()
{
    if(timer)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete timer;
    }
}

void MonitoringComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("monitoring", this);
}

void MonitoringComponent::setConfig(ConfigPtr value)
{
    BaseComponent::setConfig(value);
    monitoringConfig = value->monitoringConfig;
    loggerComponent->setConfig(value);
}

void MonitoringComponent::start()
{
    if(monitoringConfig->enabled)
    {
        timer->start(monitoringConfig->memoryCheckMills);
    }
}

void MonitoringComponent::stop()
{
    timer->stop();
}

void MonitoringComponent::onUpdate()
{
    setMemory(memoryChecker.memoryUsed());
    QString outMemory = "check memory: " +  QString::number(memoryChecker.memoryUsed()) + " MB";
    loggerComponent->log(outMemory, LogType::Verbose, LogRemoteType::Slack, true);
}

int MonitoringComponent::memory() const
{
    return _memory;
}

void MonitoringComponent::setMemory(int value)
{
    _memory = value;
    emit memoryChanged();
}
