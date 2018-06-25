#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "UserData.h"
#include "components/ArduinoComponent.h"

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

    LoginModule(QObject *parent = nullptr);

    void setArduino(ArduinoComponent* arduinoComponent);
    virtual void setConfig(Config* config) override;
    void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setUserData(UserData* userData);

    friend class LoginModuleTest;

private:
    ArduinoComponent* arduinoComponent;
    UserData* userData;

signals:
    void loginStateChanged(LoginModule::LoginState loginState);

};

#endif // LOGINMODULE_H
