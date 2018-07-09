import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../components"
import "elements"
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
        case AppState.Login:
            introScreen.visible = true;
            break;

        case AppState.Instruction:
            instructionScreen.visible = true;
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
    }

    InstructionScreen
    {
        id: instructionScreen;
        visible: false;
    }

    GameScreen
    {
        id: gameScreen;
        visible: false
    }

    ResultScreen
    {
        id: resultScreen;
        visible: false;
    }

    HealthCheckerComponent
    {
        id:health;
        y: 900;
        x: 50;
    }

    BackBtn
    {
        id:backBtn;
        x: 720;
        y: 100;
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

        introScreen.reset();
        instructionScreen.reset();
        gameScreen.reset();
        resultScreen.reset();
    }
}
