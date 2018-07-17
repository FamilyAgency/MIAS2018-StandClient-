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
    flags: Qt.SplashScreen;
    width: standData.mainConfig.touchScreen.width;
    height: standData.mainConfig.touchScreen.height;
    x: standData.mainConfig.touchScreen.x;
    y: standData.mainConfig.touchScreen.y;
    color: "#1c1c1c";

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

        case AppState.Result:
            resultScreen.visible = true;
            break;
        }
    }

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

    ResultScreen
    {
        id: resultScreen;
    }

    HealthCheckerComponent
    {
        id:health;
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

    function hideAll()
    {
        introScreen.visible = false;
        instructionScreen.visible = false;
        gameScreen.visible = false;
        resultScreen.visible = false;
        rouletteScreen.visible = false;

        introScreen.stop();
        instructionScreen.stop();
        gameScreen.stop();
        resultScreen.stop();
        rouletteScreen.stop();
    }
}
