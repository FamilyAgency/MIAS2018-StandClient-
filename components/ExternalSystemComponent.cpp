#include "ExternalSystemComponent.h"

ExternalSystemComponent::ExternalSystemComponent(QObject *parent) : BaseComponent(parent)
{

}

ExternalSystemComponent::~ExternalSystemComponent()
{

}

bool ExternalSystemComponent::isHealthy()
{
    return true;
}
