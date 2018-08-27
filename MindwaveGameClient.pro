QT += qml quick widgets serialport


CONFIG += c++11

SOURCES += main.cpp \
    config/Config.cpp \
    config/ConfigController.cpp \
    config/ConfigLoader.cpp \
    config/ConfigParser.cpp \
    config/ConfigWriter.cpp \
    core/Types.cpp \
    network/socketClient/TCPSocketClient.cpp \
    network/http/HTTPClient.cpp \
    tools/MathTools.cpp \
    components/HealthCheckerComponent.cpp \
    core/game/GameTask.cpp \
    core/game/GameTaskManager.cpp \
    core/game/VelocityCalculator.cpp \
    core/AppController.cpp \
    core/GameSession.cpp \
    components/BaseComponent.cpp \
    components/ServerComponent.cpp \
    components/ExternalSystemComponent.cpp \
    tests/MindwaveComponentTest.cpp \
    components/SlackComponent.cpp \
    services/BaseService.cpp \
    components/LoggerComponent.cpp \
    core/modules/BaseModule.cpp \
    core/modules/GameModule.cpp \
    core/modules/InstructionModule.cpp \
    core/modules/IntroModule.cpp \
    core/data/StandData.cpp \
    core/data/UserData.cpp \
    components/MonitoringComponent.cpp \
    components/monitoring/MemoryChecker.cpp \
    tools/AppSettings.cpp \
    tools/StringTools.cpp \
    core/modules/RouletteModule.cpp \
    core/modules/GameResultModule.cpp \
    core/modules/SuperGameModule.cpp \
    core/modules/SuperGameResultModule.cpp \
    core/data/OneStageData.cpp \
    components/mindwave/MindwaveParserBase.cpp \
    components/mindwave/MindwaveReaderBase.cpp \
    components/mindwave/MindwaveComponentBase.cpp \
    components/mindwave/tcp/MindwaveComponentTCP.cpp \
    components/mindwave/tcp/MindwaveReaderTCP.cpp \
    components/mindwave/tcp/MindwaveParserTCP.cpp \
    components/mindwave/serial/MindwaveComponentSerial.cpp \
    components/mindwave/serial/MindwaveReaderSerial.cpp \
    components/mindwave/serial/MindwaveParserSerial.cpp \
    components/rfid/ACR122CardHandler.cpp \
    components/rfid/UHFCardHandler.cpp \
    components/RFIDComponent.cpp \
    components/server/ServerRemoteComponent.cpp \
    tests/ServerRemoteComponentTest.cpp \
    core/modules/TestDriveModule.cpp \
    tools/FileReader.cpp \
    core/data/DilerData.cpp \
    core/game/GameCountDown.cpp \
    core/game/GameCountDown.cpp \
    core/game/GameCountDown.cpp \
    core/data/SuperGameData.cpp \
    tools/AnimationManager.cpp \
    core/data/AdvantagesData.cpp \
    components/mindwave/serial/SerialThread.cpp \
    core/data/GameComplexityData.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += winscard/include

LIBS += -L"$$PWD/winscard/lib" -lWinscard

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config/Config.h \
    config/ConfigController.h \
    config/ConfigLoader.h \
    config/ConfigParser.h \
    config/ConfigWriter.h \
    core/Types.h \
    network/socketClient/TCPSocketClient.h \
    network/http/HTTPClient.h \
    tools/MathTools.h \
    core/game/GameTask.h \
    core/game/GameTaskManager.h \
    core/game/VelocityCalculator.h \
    core/AppController.h \
    core/GameSession.h \   
    components/BaseComponent.h \
    components/ServerComponent.h \
    components/ExternalSystemComponent.h \
    tests/MindwaveComponentTest.h \
    components/SlackComponent.h \
    services/BaseService.h \
    components/RFIDComponent.h \
    components/LoggerComponent.h \
    core/modules/BaseModule.h \
    core/modules/GameModule.h \
    core/modules/InstructionModule.h \
    core/modules/IntroModule.h \
    core/data/StandData.h \
    core/data/UserData.h \
    components/MonitoringComponent.h \
    components/monitoring/MemoryChecker.h \
    tools/AppSettings.h \
    tools/StringTools.h \
    core/modules/RouletteModule.h \
    core/modules/GameResultModule.h \
    core/modules/SuperGameModule.h \
    core/modules/SuperGameResultModule.h \
    core/data/OneStageData.h \
    components/mindwave/MindwaveParserBase.h \
    components/mindwave/MindwaveReaderBase.h \
    components/mindwave/MindwaveComponentBase.h \
    components/mindwave/tcp/MindwaveComponentTCP.h \
    components/mindwave/tcp/MindwaveReaderTCP.h \
    components/mindwave/tcp/MindwaveParserTCP.h \
    components/mindwave/serial/MindwaveComponentSerial.h \
    components/mindwave/serial/MindwaveReaderSerial.h \
    components/mindwave/serial/MindwaveParserSerial.h \
    components/mindwave/serial/MindwaveSerialData.h \
    components/rfid/ACR122CardHandler.h \
    components/rfid/UHFCardHandler.h \
    components/mindwave/serial/mindwaveserialdata.h \
    components/monitoring/MemoryChecker.h \
    components/ExternalSystemComponent.h \
    components/HealthCheckerComponent.h \
    components/MonitoringComponent.h \
    components/ServerComponent.h \
    core/modules/BaseModule.h \
    core/modules/GameModule.h \
    core/modules/GameResultModule.h \
    core/modules/InstructionModule.h \
    core/modules/IntroModule.h \
    components/server/ServerRemoteComponent.h \
    tests/ServerRemoteComponentTest.h \
    core/modules/TestDriveModule.h \
    tools/FileReader.h \
    core/data/DilerData.h \
    core/game/GameCountDown.h \
    core/data/SuperGameData.h \
    tools/AnimationManager.h \
    core/data/AdvantagesData.h \
    components/mindwave/serial/SerialThread.h \
    core/data/GameComplexityData.h

DISTFILES += \
    modules/components/components.pri \
    core/data/AdvantagesData.qml
