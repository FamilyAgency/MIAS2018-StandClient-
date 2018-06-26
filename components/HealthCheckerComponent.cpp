#include "HealthCheckerComponent.h"

HealthCheckerComponent::HealthCheckerComponent(QObject *parent) : BaseComponent(parent)
{

}

void HealthCheckerComponent::addComponent(BaseComponent* component)
{
    components.append(component);
}
