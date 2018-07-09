#ifndef HEALTHCHECKERCOMPONENT_H
#define HEALTHCHECKERCOMPONENT_H

#include <QObject>
#include "RFIDComponent.h"
#include "MindwaveComponent.h"

class HealthCheckerComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit HealthCheckerComponent(QObject *parent = nullptr);
    virtual ~HealthCheckerComponent();

    Q_INVOKABLE QVariantList getInfo() const;

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void start() override;
    virtual void stop() override;

    void addComponent(QSharedPointer<ExternalSystemComponent> component);

private:
     QList<QSharedPointer<ExternalSystemComponent>> components;

};

#endif // HEALTHCHECKERCOMPONENT_H
