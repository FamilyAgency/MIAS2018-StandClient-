#ifndef HEALTHCHECKERCOMPONENT_H
#define HEALTHCHECKERCOMPONENT_H

#include <QObject>
#include "ArduinoComponent.h"
#include "MindwaveComponent.h"

class HealthCheckerComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit HealthCheckerComponent(QObject *parent = nullptr);
    virtual void setQmlContext(QQmlContext* value) override;

    void addComponent(ExternalSystemComponent* component);

    Q_INVOKABLE QVariantList getInfo() const;

private:
     QList<ExternalSystemComponent*> components;

signals:

public slots:
};

#endif // HEALTHCHECKERCOMPONENT_H
