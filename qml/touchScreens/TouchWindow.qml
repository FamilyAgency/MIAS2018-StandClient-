import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../components"
import "elements"
import com.app 1.0
import QtMultimedia 5.8

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

    Video
    {
        id: player;
        anchors.fill: parent;
        anchors.centerIn: parent;
        playlist:
            Playlist
        {
            id: playlist

        }
    }

    Component.onCompleted:
    {
        console.log("url", videos.intro1Path)
        playlist.addItem(videos.intro1Path)
        playlist.addItem(videos.intro2Path)
        playlist.addItem(videos.instructionPath)
        playlist.addItem(videos.bgLoop)
    }

    Button
    {
        text:"Next video"
        onClicked:
        {
            playlist.next();
            player.play();
        }

    }

    //    Item
    //    {
    //        id: screens;
    //        anchors.fill: parent;
    //    }

    //    HealthCheckerComponent
    //    {
    //        id:health;
    //        x: 50;
    //        visible: false;
    //        anchors.bottom: parent.bottom;
    //        anchors.bottomMargin: 200;
    //    }

    //    ServerPreloader
    //    {
    //        id: serverPreloader;
    //    }

    //    AnimationControllerLayer
    //    {
    //        id: animationController;
    //    }

    //    ServerErrorPopup
    //    {
    //        id: serverErrorPopup;
    //    }

    //    SecretBackBtn
    //    {
    //        id: backBtn;
    //    }

    //    Component.onCompleted:
    //    {
    //        addLocation(AppState.Intro, "IntroScreen");
    //        addLocation(AppState.Instruction, "InstructionScreen");
    //        addLocation(AppState.Roulette, "RouletteScreen");
    //        addLocation(AppState.Game, "GameScreen");
    //        addLocation(AppState.GameResult, "GameResultScreen");
    //        addLocation(AppState.SuperGame, "SuperGameScreen");
    //        addLocation(AppState.SuperGameResult, "SuperGameResultScreen");
    //        addLocation(AppState.TestDrive, "TestDriveScreen");

    //        setState(appController.getAppState());
    //    }

    //    Connections
    //    {
    //        target: appController;

    //        onAppStateChanged:
    //        {
    //            console.log("touch app state changes :::::::::::::", appState);
    //            setState(appState);
    //        }
    //    }

    //    function addLocation(type, component)
    //    {
    //        var componentQML = Qt.createComponent(component + ".qml");
    //        var location = componentQML.createObject(screens);
    //        location["onAnimComplete"].connect(function() { onAnimComplete() });
    //        location["onAnimStart"].connect(function() { onAnimStart() });
    //        locations.push({"loc": location, "type": type});
    //    }

    //    function setState(appState)
    //    {
    //        hideAll();
    //        animationController.show();

    //        for(var i = 0; i < locations.length; i++)
    //        {
    //            if(locations[i].type === appState)
    //            {
    //                locations[i].loc.start();
    //                break;
    //            }
    //        }
    //    }

    //    function onAnimComplete()
    //    {
    //        animationController.hide();
    //    }

    //    function onAnimStart()
    //    {
    //        animationController.show();
    //    }

    //    function hideAll()
    //    {
    //        for(var i = 0; i < locations.length; i++)
    //        {
    //            locations[i].loc.stop();
    //        }
    //    }
}
