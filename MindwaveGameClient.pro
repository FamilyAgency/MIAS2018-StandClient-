QT += qml quick charts widgets serialport


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
    components/MindwaveComponent.cpp \
    core/game/GamePostTask.cpp \
    core/game/GamePreTask.cpp \
    core/game/GameTask.cpp \
    core/game/GameTaskManager.cpp \
    core/game/TaskCreator.cpp \
    core/game/VelocityCalculator.cpp \
    core/AppController.cpp \
    core/GameSession.cpp \
    components/BaseComponent.cpp \
    components/ServerComponent.cpp \
    components/ExternalSystemComponent.cpp \
    tests/MindwaveComponentTest.cpp \
    components/mindwave/MindwaveReader.cpp \
    components/mindwave/MindwaveParser.cpp \
    components/SlackComponent.cpp \
    services/BaseService.cpp \
    core/game/GameProgress.cpp \
    core/game/OneGameData.cpp \
    components/RFIDComponent.cpp \
    components/rfid/BaseRFIDDataReader.cpp \
    components/rfid/UHFDataReader.cpp \
    components/rfid/UHFJsonDataReader.cpp \
    tests/ServerComponentTest.cpp \
    components/LoggerComponent.cpp \
    core/modules/BaseModule.cpp \
    core/modules/GameModule.cpp \
    core/modules/InstructionModule.cpp \
    core/modules/IntroModule.cpp \
    core/data/StandData.cpp \
    core/data/UserData.cpp \
    tests/RFIDComponentTest.cpp \
    components/MonitoringComponent.cpp \
    components/monitoring/MemoryChecker.cpp \
    components/ServerRemoteComponent.cpp \
    tools/AppSettings.cpp \
    tools/StringTools.cpp \
    core/modules/RouletteModule.cpp \
    core/modules/GameResultModule.cpp \
    core/modules/SuperGameModule.cpp

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
    components/HealthCheckerComponent.h \
    components/MindwaveComponent.h \
    core/game/GamePostTask.h \
    core/game/GamePreTask.h \
    core/game/GameTask.h \
    core/game/GameTaskManager.h \
    core/game/TaskCreator.h \
    core/game/VelocityCalculator.h \
    core/AppController.h \
    core/GameSession.h \   
    components/BaseComponent.h \
    components/ServerComponent.h \
    components/ExternalSystemComponent.h \
    tests/MindwaveComponentTest.h \
    components/mindwave/MindwaveReader.h \
    components/mindwave/MindwaveParser.h \
    components/SlackComponent.h \
    services/BaseService.h \
    core/game/GameProgress.h \
    core/game/OneGameData.h \
    components/RFIDComponent.h \
    components/rfid/BaseRFIDDataReader.h \
    components/rfid/UHFDataReader.h \
    components/rfid/UHFJsonDataReader.h \
    tests/ServerComponentTest.h \
    components/LoggerComponent.h \
    core/modules/BaseModule.h \
    core/modules/GameModule.h \
    core/modules/InstructionModule.h \
    core/modules/IntroModule.h \
    core/data/StandData.h \
    core/data/UserData.h \
    tests/RFIDComponentTest.h \
    components/MonitoringComponent.h \
    components/monitoring/MemoryChecker.h \
    components/ServerRemoteComponent.h \
    tools/AppSettings.h \
    tools/StringTools.h \
    core/modules/RouletteModule.h \
    core/modules/GameResultModule.h \
    core/modules/SuperGameModule.h

DISTFILES +=
