#ifndef EXTERNALSYSTEMCOMPONENT_H
#define EXTERNALSYSTEMCOMPONENT_H

#include <QObject>
#include "components/BaseComponent.h"

class ExternalSystemComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit ExternalSystemComponent(QObject *parent = nullptr);

    virtual bool isHealthy() = 0;

signals:

public slots:
};

#endif // EXTERNALSYSTEMCOMPONENT_H
