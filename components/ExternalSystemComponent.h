#ifndef EXTERNALSYSTEMCOMPONENT_H
#define EXTERNALSYSTEMCOMPONENT_H

#include <QObject>
#include "components/BaseComponent.h"

class ExternalSystemComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit ExternalSystemComponent(QObject *parent = nullptr);
    virtual ~ExternalSystemComponent();
    virtual bool isHealthy() = 0;
};

#endif // EXTERNALSYSTEMCOMPONENT_H
