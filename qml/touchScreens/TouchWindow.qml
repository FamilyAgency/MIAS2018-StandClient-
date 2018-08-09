import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../components"
import "elements"
import com.app 1.0

Item
{
    id: touchCore;
    anchors.fill: parent;
    anchors.centerIn: parent;

    property var locations: [];

    VideoManager
    {
        id: videos;
    }

    Item
    {
        id: screens;
        anchors.fill: parent;
        z: 3;
    }

    HealthCheckerComponent
    {
        id:health;
        x: 50;
        visible: false;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 200;
        z: 4;
    }

    ServerPreloader
    {
        id: serverPreloader;
        z: 4;
    }

    AnimationControllerLayer
    {
        id: animationController;
        z: 4;
    }

    ServerErrorPopup
    {
        id: serverErrorPopup;
        z: 4;
    }

    SecretBackBtn
    {
        id: backBtn;
        z: 4;
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
       // appController.setAppStateTest(AppState.GameResult);
        // advatage.stageCompleted("Система<br/>предупреждения<br/>столкновения сбоку", "при выезде с парковки<br/>задним ходом", "content/video/1.mp4");
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
