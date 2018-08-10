import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtMultimedia 5.8

import com.app 1.0

Item
{
    property string intro1Path: configController.getVideoFileInAppDir("intro1");
    property string intro2Path: configController.getVideoFileInAppDir("intro2");
    property string instructionPath: configController.getVideoFileInAppDir("instruction");
    property string bgLoop: configController.getVideoFileInAppDir("bgloop");
    property string gameresult: configController.getVideoFileInAppDir("gameresult");


    anchors.fill: parent;

    Video
    {
        id: player1;
        anchors.fill: parent;
        anchors.centerIn: parent;
        loops: MediaPlayer.Infinite;
        playlist:
            Playlist
        {
            id: playlist1;
        }

        OpacityAnimator on opacity
        {
            id:videoAnim1;
            from: 0;
            to: 1;
            duration: 500;
            running:false;

            onStopped:
            {
                console.log(("VIDEO PLAYER HIDE"))
               player2.seek(0);
            }
        }
    }

    Video
    {
        id: player2;
        anchors.fill: parent;
        anchors.centerIn: parent;
        opacity: 0;
        loops: MediaPlayer.Infinite;
        playlist:
            Playlist
        {
            id: playlist2;
        }

        OpacityAnimator on opacity
        {
            id:videoAnim2;
            from: 0;
            to: 1;
            duration: 500;
            running:false;

            onStopped:
            {
                player1.seek(0);
            }
        }
    }


//    Button
//    {
//        text:"Next video"
//        onClicked:
//        {
//            playlist2.next();
//            player2.play();
//        }
//    }

    Component.onCompleted:
    {
        playlist1.addItem(intro1Path);
        playlist1.addItem(intro2Path);
        playlist1.addItem(instructionPath);
        playlist1.addItem(bgLoop);
        playlist1.addItem(gameresult);


        playlist2.addItem(intro1Path);
        playlist2.addItem(intro2Path);
        playlist2.addItem(instructionPath);
        playlist2.addItem(bgLoop);
        playlist2.addItem(gameresult);

        setState(appController.getAppState());

        positionTimer.start();
    }


    property var currentState: -1;
    property var currentPlayer: player2;
    property var currentPlaylist: playlist2;
    property var currentVideoAnim: videoAnim2;

    Connections
    {
        target: appController;

        onAppStateChanged:
        {
            console.log("touch app state changes in video controller :::::::::::::", appState);

            setState(appState);
        }
    }

    Connections
    {
        target:introModule;

        onUserStartPlay:
        {
            startIndex(1);
        }

        onUserNotFound:
        {
            startIndex(1);
        }

        onUserCantStartReason:
        {
            startIndex(1);
        }
    }

    function setState(appState)
    {
        //        if(currentState == appState)
        //        {
        //            return;
        //        }

        console.log("swaaaaaaaaap")

        positionTimer.stop();
        needLoop = false;

        switch(appState)
        {
        case AppState.Intro:
            startIndex(0);
            break;

        case AppState.Instruction:
            startIndex(2);
            break;

        case AppState.Roulette:
        case AppState.Game:
            startIndex(3);
            break;
        case AppState.GameResult:
            needLoop = true;
            loopThreshold = 8300;
            startIndex(4);
            break;

        case AppState.SuperGame:
            startIndex(3);
            break;

        case AppState.SuperGameResult:
        case AppState.TestDrive:
            startIndex(3);
            break;

        }
        currentState = appState;
        positionTimer.start();
    }

    property bool needLoop: false;
    property real loopThreshold: 0;

    Timer
    {
        id: positionTimer;
        running: false;
        interval: 100;
        repeat: true;
        onTriggered:
        {
            if(needLoop)
            {
               // console.log(currentPlayer.position, currentPlayer.duration)
                if(currentPlayer.position >= currentPlayer.duration - 500)
                {
                  //  currentPlayer.seek(loopThreshold);
                }
            }
        }
    }


    function startIndex(index, seekTo)
    {
        /*if (seekTo === undefined)*/ seekTo = 0;
        swapVideos();
        currentPlaylist.currentIndex = index;
        currentPlayer.seek(seekTo);
        currentPlayer.play();
        playAnim();
    }

    function swapVideos()
    {
        if(currentPlayer == player2)
        {
            console.log("------------------------ currentPlayer")
            currentPlayer = player1;
            currentPlaylist = playlist1;
            currentVideoAnim = videoAnim1;
        }
        else if(currentPlayer == player1)
        {
            console.log("------------------------ currentPlayer2")

            currentPlayer = player2;
            currentPlaylist = playlist2;
            currentVideoAnim = videoAnim2;
        }
    }

    function playAnim()
    {
        currentPlayer.opacity = 0;
        currentPlayer.z = 1;
        getOppositePlayer().z = 0;
        currentVideoAnim.start();
    }

    function getOppositePlayer()
    {
        return  currentPlayer == player1 ? player2 : player1;
    }
}
