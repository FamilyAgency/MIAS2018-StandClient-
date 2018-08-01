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
    title: "Touch Window";
    x: standData.mainConfig.touchScreen.x;
    y: standData.mainConfig.touchScreen.y;
    width: standData.mainConfig.touchScreen.width;
    height: standData.mainConfig.touchScreen.height;
    visible: true;
    flags: standData.mainConfig.touchScreenIsSplash ? Qt.SplashScreen : Qt.Window;
    color: "#1c1c1c";

    id: touchCore;

    property var locations: [];

    Item
    {
        id: screens;
        anchors.fill: parent;
    }

    HealthCheckerComponent
    {
        id:health;
        x: 50;
        visible: false;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 200;
    }

    ServerPreloader
    {
        id: serverPreloader;
    }

    AnimationControllerLayer
    {
        id: animationController;
    }

    ServerErrorPopup
    {
        id: serverErrorPopup;
    }

    BackBtn
    {
        id: backBtn;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.right: parent.right;
        anchors.rightMargin: 100;
    }

    Component.onCompleted:
    {
        addLocation(AppState.Intro, "IntroScreen");
        addLocation(AppState.Instruction, "InstructionScreen");
        addLocation(AppState.Roulette, "RouletteScreen");
        addLocation(AppState.Game, "GameScreen");
        addLocation(AppState.GameResult, "GameResultScreen");
        addLocation(AppState.SuperGame, "SuperGameScreen");
        addLocation(AppState.SuperGameResult, "SuperGameResultScreen");
        addLocation(AppState.TestDrive, "TestDriveScreen");

        setState(appController.getAppState());
    }

    Connections
    {
        target: appController;

        onAppStateChanged:
        {
            console.log("touch app state changes :::::::::::::", appState);
            setState(appState);
        }
    }

    function addLocation(type, component)
    {
        var componentQML = Qt.createComponent(component + ".qml");
        var location = componentQML.createObject(screens);
        location["onAnimComplete"].connect(function() { onAnimComplete() });
        location["onAnimStart"].connect(function() { onAnimStart() });
        locations.push({"loc": location, "type": type});
    }

    function setState(appState)
    {
        hideAll();
        animationController.show();

        for(var i = 0; i < locations.length; i++)
        {
            if(locations[i].type === appState)
            {
                locations[i].loc.start();
                break;
            }
        }
    }

    function onAnimComplete()
    {
        animationController.hide();
    }

    function onAnimStart()
    {
        animationController.show();
    }

    function hideAll()
    {
        for(var i = 0; i < locations.length; i++)
        {
            locations[i].loc.stop();
        }
    }
}
