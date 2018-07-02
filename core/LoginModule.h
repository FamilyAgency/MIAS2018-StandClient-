#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "UserData.h"
#include "components/RFIDComponent.h"

class LoginModule : public BaseModule
{
    Q_OBJECT
public:    
    enum class LoginError
    {
        UserDoesntExist,
        WasRecently,
        ServerError,
        ArduinoError,
        Undefined
    };
    Q_ENUMS(LoginError)

    enum class LoginState
    {       
        Login,
        Logout,
        Error
    };
    Q_ENUMS(LoginState)

    enum class UserState
    {
        None,
        CanPlay,
        DoesntExists,
        Finished,
        WasRecently,
        YouArePlaying
    };
    Q_ENUMS(UserState)

    LoginModule(QObject *parent = nullptr);

    void setRFIDComponent(RFIDComponent* rfidComponent);
    virtual void setConfig(Config* config) override;
    void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setUserData(UserData* userData);
    virtual QString getName() const override;

    QString getStringState() const;

    friend class LoginModuleTest;

private:
    RFIDComponent* rfidComponent;
    UserData* userData;
    LoginState state = LoginState::Logout;
    UserState userState = UserState::None;

    void setState(LoginState state);
    void setUserState(UserState value);

signals:
    void loginStateChanged(LoginModule::LoginState loginState);
    void userStateChanged(LoginModule::UserState userState);

};

#endif // LOGINMODULE_H
