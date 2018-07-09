#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class BaseModule : public QObject
{
    Q_OBJECT
public:
    explicit BaseModule(QObject *parent = nullptr);
    virtual ~BaseModule();

    virtual void setQmlContext(QQmlContext* qmlContext);
    virtual void setConfig(ConfigPtr config);
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual QString getName() const = 0;

protected:
    ConfigPtr config;
    QQmlContext* qmlContext;

};

#endif // BASEMODULE_H
