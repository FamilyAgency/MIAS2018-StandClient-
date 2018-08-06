//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QScopedPointer>

#include "config/ConfigController.h"
#include "core/AppController.h"
#include "core/modules/IntroModule.h"
#include "components/rfid/ACR122CardHandler.h"

#include <QQuickWindow>
#include <QQuickWindow>

int main(int argc, char *argv[])
{ 
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::OpenGL);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QScopedPointer<ConfigController> configController(new ConfigController);
    engine.rootContext()->setContextProperty("configController", configController.data());

    QScopedPointer<AppController> appController(new AppController());
    engine.rootContext()->setContextProperty("appController", appController.data());

    qmlRegisterType<AppController>("com.app", 1, 0, "AppState");
    qRegisterMetaType<CantPlayReason>("CantPlayReason");
    qmlRegisterUncreatableType<UserData>("com.app", 1, 0, "CantPlayReason", "CantPlayReason enum type");

    qRegisterMetaType<ServerStatus>("ServerStatus");
    qmlRegisterUncreatableType<ServerComponent>("com.app", 1, 0, "ServerStatus", "ServerStatus enum type");
    qRegisterMetaType<ServerStatus>("ResponseType");
    qmlRegisterUncreatableType<ServerComponent>("com.app", 1, 0, "ResponseType", "ResponseType enum type");
    qRegisterMetaType<ServerStatus>("ServerGlobalErrorType");
    qmlRegisterUncreatableType<ServerComponent>("com.app", 1, 0, "ServerGlobalErrorType", "ServerGlobalErrorType enum type");

    qmlRegisterType<MindwaveComponentBase>("com.app", 1, 0, "DeviceState");
    qmlRegisterType<RFIDComponent>("com.app", 1, 0, "CardReaderState");
    qmlRegisterType<ACR122CardHandler>("com.app", 1, 0, "CardReaderError");

    QObject::connect(configController.data(), &ConfigController::configServiceReady,[&](ConfigPtr conf)
    {
        appController->onConfigLoaded(conf);
        appController.data()->setQmlContext(engine.rootContext());

        engine.load(QUrl(QLatin1String(conf->mainConfig->qmlOnStart.toLatin1())));

        if (engine.rootObjects().isEmpty())
        {
            return -1;
        }

        return 1;
    });

    QObject::connect(configController.data(), &ConfigController::configServiceError, [&](const QString& message)
    {
        engine.load(QUrl(QLatin1String("qrc:/qml/ConfigErrorWindow.qml")));

        if (engine.rootObjects().isEmpty())
        {
            return -1;
        }

        return 1;
    });

    // config load. entry point
    configController.data()->setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD::LOCAL_FILE);
    configController.data()->load();

    return app.exec();
}
