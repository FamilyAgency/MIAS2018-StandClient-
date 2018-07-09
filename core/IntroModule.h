#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "UserData.h"
#include "components/RFIDComponent.h"
#include "components/ServerComponent.h"
#include "core/StandData.h"

class IntroModule : public BaseModule
{
    Q_OBJECT
public:
    IntroModule(QObject *parent = nullptr);

    virtual void setRFIDComponent(RFIDComponent* rfidComponent);
    virtual void setServerComponent(ServerComponent* value);
    virtual void setUserData(UserData* userData);
    virtual void setStandData(StandData* value);

    virtual void setConfig(ConfigPtr config) override;
    void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;    
    virtual QString getName() const override;

    QString getStringState() const;

    friend class IntroModuleTest;

private:
    RFIDComponent* rfidComponent = nullptr;
    ServerComponent* serverComponent = nullptr;
    UserData* userData = nullptr;
    StandData* standData = nullptr;
    LoginState state = LoginState::Logout;
    UserState userState = UserState::None;

    void setState(LoginState state);
    void setUserState(UserState value);
    void parseServerResponse(const QString& data);

signals:
    void loginStateChanged(LoginState loginState);
    void userStateChanged(UserState userState);

private slots:
    void onRFIDRecieve(int id);
    void onServerResponse(const ServerResponse& response);
    void onServerError();

};

#endif // LOGINMODULE_H
