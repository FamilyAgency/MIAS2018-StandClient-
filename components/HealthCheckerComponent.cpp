#include "HealthCheckerComponent.h"

HealthCheckerComponent::HealthCheckerComponent(QObject *parent) : BaseComponent(parent)
{
    name = "HealthChecker";
}

HealthCheckerComponent::~HealthCheckerComponent()
{

}

void HealthCheckerComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("healthChecker", this);
}

void HealthCheckerComponent::addComponent(QSharedPointer<ExternalSystemComponent> component)
{
    components.append(component);
}

void HealthCheckerComponent::start()
{

}

void HealthCheckerComponent::stop()
{

}

QVariantList HealthCheckerComponent::getInfo() const
{
    QVariantList info;
    for(auto comp: components)
    {
        if(comp->isHealthy())
        {
            info.append(comp->getName() + " alive");
        }
        else
        {
            info.append(comp->getName() + " dead");
        }

    }
    return info;
}
