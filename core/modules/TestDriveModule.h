#ifndef TESTDRIVEMODULE_H
#define TESTDRIVEMODULE_H

#include <QObject>
#include <QVariantList>
#include "BaseModule.h"

#include "components/ServerComponent.h"
#include "core/data/UserData.h"
#include "core/data/DilerData.h"

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

    void setServerComponent(QSharedPointer<ServerComponent> value);
    void setUser(QSharedPointer<UserData> value);
    void setDilerData(QSharedPointer<DilerData> value);

    Q_INVOKABLE void makeTestDrive(int dealerId);

private:
    QSharedPointer<ServerComponent> serverComponent;
    QSharedPointer<UserData> currentUser;
    QSharedPointer<DilerData> dilerData;

signals:
    void dilersDataUpdated(const QVariantList& dilersData);

private slots:
    void onDilersDataUpdated(const QVariantList& data);

};

#endif // TESTDRIVEMODULE_H
