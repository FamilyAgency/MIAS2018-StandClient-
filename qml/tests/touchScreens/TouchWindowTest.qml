import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../../components"
import "../../touchScreens/elements"
import "../../touchScreens"
import com.app 1.0

Window
{
    objectName: "touchWindow";
    title: "Touch Window";
    visible: true;
    id: touchCore;
    flags: standData.mainConfig.touchScreenIsSplash ? Qt.SplashScreen : Qt.Window;
    width: standData.mainConfig.touchScreen.width;
    height: standData.mainConfig.touchScreen.height;
    x: standData.mainConfig.touchScreen.x;
    y: standData.mainConfig.touchScreen.y;
    color: "#1c1c1c";

    IntroScreen
    {
        id: introScreen;

        IntroScreenTest
        {

        }
    }

    InstructionScreen
    {
        id: instructionScreen;
    }

    RouletteScreen
    {
        id: rouletteScreen;
    }

    GameScreen
    {
        id: gameScreen;
    }

    GameResultScreen
    {
        id: gameResultScreen;
    }

    SuperGameScreen
    {
        id: superGameScreen;
    }

    SuperGameResultScreen
    {
        id: superGameResultScreen;
    }

    HealthCheckerComponent
    {
        id:health;
        visible:false;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 200;
        x: 50;
    }



    BackBtn
    {
        id:backBtn;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.right: parent.right;
        anchors.rightMargin: 100;
    }

    ServerPreloader
    {
        id: serverPreloader;
    }

    ServerErrorPopup
    {
        id: serverErrorPopup;
    }

    Component.onCompleted:
    {
        setState(appController.getAppState());
    }

    Connections
    {
        target:appController;
        onAppStateChanged:
        {
            console.log("touch app state changes :::::::::::::", appState);
            setState(appState);
        }
    }

    function setState(appState)
    {
        hideAll();
        switch(appState)
        {
        case AppState.Intro:
            introScreen.visible = true;
            break;

        case AppState.Instruction:
            instructionScreen.visible = true;
            break;

        case AppState.Roulette:
            rouletteScreen.visible = true;
            break;

        case AppState.Game:
            gameScreen.visible = true;
            break;

        case AppState.GameResult:
            gameResultScreen.visible = true;
            break;

        case AppState.SuperGame:
            superGameScreen.visible = true;
            break;

        case AppState.SuperGameResult:
            superGameResultScreen.visible = true;
            break;
        }
    }

    function hideAll()
    {
        introScreen.visible = false;
        instructionScreen.visible = false;
        gameScreen.visible = false;
        gameResultScreen.visible = false;
        rouletteScreen.visible = false;
        superGameScreen.visible = false;
        superGameResultScreen.visible = false;

        introScreen.stop();
        instructionScreen.stop();
        gameScreen.stop();
        gameResultScreen.stop();
        rouletteScreen.stop();
        superGameScreen.stop();
        superGameResultScreen.stop();
    }
}
