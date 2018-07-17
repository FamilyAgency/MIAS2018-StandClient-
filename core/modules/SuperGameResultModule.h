#ifndef SUPERGAMERESULTMODULE_H
#define SUPERGAMERESULTMODULE_H

#include <QObject>
#include "BaseModule.h"

class SuperGameResultModule : public BaseModule
{
    Q_OBJECT
public:
    explicit SuperGameResultModule(QObject *parent = nullptr);

    virtual ~SuperGameResultModule();
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

signals:

public slots:
};

#endif // SUPERGAMERESULTMODULE_H
