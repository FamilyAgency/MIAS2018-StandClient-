#ifndef MONITORINGCOMPONENT_H
#define MONITORINGCOMPONENT_H

#include "components/BaseComponent.h"
#include <QObject>
#include <QTimer>
#include "config/Config.h"
#include "monitoring/MemoryChecker.h"
#include "components/LoggerComponent.h"

class MonitoringComponent : public BaseComponent
{
    Q_OBJECT

    Q_PROPERTY(int memory READ memory WRITE setMemory NOTIFY memoryChanged)

public:
    explicit MonitoringComponent(QObject *parent = nullptr);
    virtual ~MonitoringComponent();

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr value) override;
    virtual void start() override;
    virtual void stop() override;

    int memory() const;
    void setMemory(int value);

private:
   QSharedPointer<MonitoringConfig> monitoringConfig;
   QTimer* timer;
   MemoryChecker memoryChecker;
   QSharedPointer<LoggerComponent> loggerComponent;
   int _memory = 0;

signals:
   void memoryChanged();

private slots:
    void onUpdate();
};

#endif // MONITORINGCOMPONENT_H
