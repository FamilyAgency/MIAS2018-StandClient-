#ifndef TESTDRIVEMODULE_H
#define TESTDRIVEMODULE_H

#include <QObject>
#include "BaseModule.h"

class TestDriveModule : public BaseModule
{
    Q_OBJECT
public:
    explicit TestDriveModule(QObject *parent = nullptr);
    virtual ~TestDriveModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
};

#endif // TESTDRIVEMODULE_H
