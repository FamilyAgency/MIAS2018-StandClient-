#ifndef ROULETTEMODULE_H
#define ROULETTEMODULE_H

#include <QObject>
#include "BaseModule.h"

class RouletteModule : public BaseModule
{
    Q_OBJECT
public:
    explicit RouletteModule(QObject *parent = nullptr);

    virtual ~RouletteModule();
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

signals:

public slots:
};


#endif // ROULETTEMODULE_H
