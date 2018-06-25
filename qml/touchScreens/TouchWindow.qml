import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../components"

import com.app 1.0

Window {
    objectName: "touchWindow"
    visible: true
    id: touchCore
    title: "Splash Window"
    flags: Qt.SplashScreen
    x: 1920
    width: 820
    height: 1080

    Connections
    {
        target:appController;
        onAppStateChanged:
        {
            console.log("app state changes :::::::::::::", appState);
            setState(appState);
        }
    }


    Connections
    {
        target: gameTaskManager

        onAllTaskComleteEvent:
        {
            setState(AppState.Result);
        }
    }

    Connections
    {
        target:loginModule;
        onLoginStateChanged:
        {
            switch(loginState)
            {
                case LoginState.Logout:
                     hideAll();
                     loginScreen.visible = true;
                break;
            }
        }
    }

    function setState(appState)
    {
        hideAll();
        switch(appState)
        {
        case AppState.Login:
            loginScreen.visible = true;
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

    LoginScreen
    {
        id: loginScreen;
    }

    InstructionScreen
    {
        id: instructionScreen;
        visible: false
    }

    GameScreen
    {
        id: gameScreen;
        visible: false
    }

    ResultScreen
    {
        id: resultScreen;
        visible: false
    }

    HealthCheckerComponent
    {
        id:health
        y: 1000
        x: 50
    }

    BackBtn
    {
        id:backBtn
        x: 720
        y: 100
    }

    function hideAll()
    {
        loginScreen.visible = false;
        instructionScreen.visible = false;
        gameScreen.visible = false;
        resultScreen.visible = false;

        loginScreen.reset();
        instructionScreen.reset();
        gameScreen.reset();
        resultScreen.reset();
    }
}
