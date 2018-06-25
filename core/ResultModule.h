#ifndef RESULTMODULE_H
#define RESULTMODULE_H

#include <QObject>
#include "BaseModule.h"

class ResultModule : public BaseModule
{
    Q_OBJECT
public:
    explicit ResultModule(QObject *parent = nullptr);

    virtual void start() override;
    virtual void stop() override;

signals:

public slots:
};

#endif // RESULTMODULE_H
