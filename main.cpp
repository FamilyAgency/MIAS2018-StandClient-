#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QScopedPointer>

#include "config/ConfigController.h"
#include "core/AppController.h"
#include "core/modules/IntroModule.h"

int main(int argc, char *argv[])
{ 
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;




    QScopedPointer<ConfigController> configController(new ConfigController);
    engine.rootContext()->setContextProperty("configController", configController.data());

    QScopedPointer<AppController> appController(new AppController());
    engine.rootContext()->setContextProperty("appController", appController.data());
    appController.data()->setQmlContext(engine.rootContext());

   QObject::connect(configController.data(), SIGNAL(configServiceReady(ConfigPtr)), appController.data(), SLOT(onConfigLoaded(ConfigPtr)));
   QObject::connect(configController.data(), SIGNAL(configServiceError()), appController.data(), SLOT(onConfigError()));



    qmlRegisterType<AppController>("com.app", 1, 0, "AppState");
    qmlRegisterType<UserData>("com.app", 1, 0, "LoginState");
    qmlRegisterType<UserData>("com.app", 1, 0, "UserState");
    qmlRegisterType<ServerComponent>("com.app", 1, 0, "ServerStatus");
    qmlRegisterType<ServerComponent>("com.app", 1, 0, "RegistrationError");
    qmlRegisterType<ServerComponent>("com.app", 1, 0, "ResponseType");
    qmlRegisterType<ServerComponent>("com.app", 1, 0, "ServerGlobalErrorType");


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // config load. entry point
    configController.data()->setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE);
    configController.data()->load();

    return app.exec();
}
