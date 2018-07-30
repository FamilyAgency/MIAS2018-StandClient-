#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "core/data/UserData.h"
#include "components/RFIDComponent.h"
#include "components/server/ServerRemoteComponent.h"
#include "core/data/StandData.h"

class IntroModule : public BaseModule
{
    Q_OBJECT
public:
    explicit IntroModule(QObject *parent = nullptr);
    virtual ~IntroModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    virtual void setRFIDComponent(QSharedPointer<RFIDComponent> rfidComponent);
    virtual void setServerComponent(QSharedPointer<ServerComponent> value);
    virtual void setUserData(QSharedPointer<UserData> userData);
    virtual void setStandData(QSharedPointer<StandData> value);

private:
    QSharedPointer<RFIDComponent> rfidComponent = nullptr;
    QSharedPointer<ServerRemoteComponent> serverComponent = nullptr;
    QSharedPointer<UserData> userData = nullptr;
    QSharedPointer<StandData> standData = nullptr;

    void connectComponents();
    void disconnectComponents();

signals:
    void userStartPlay();
    void userNotFound();


private slots:
    void onUserReadSuccess(const QString& data);

    void onNewUserEntered(const UserObject& userObject);
    void onUserNotFound();
    void onServerError();
};

#endif // LOGINMODULE_H
