import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtMultimedia 5.8

import "elements"
import com.app 1.0

Item
{
    property string intro1Path: configController.getVideoFileInAppDir("intro1.mp4");
    property string intro2Path: configController.getVideoFileInAppDir("intro2.mp4");
    property string instructionPath: configController.getVideoFileInAppDir("instruction.mp4");
    property string bgLoop: configController.getVideoFileInAppDir("bgloop.mp4");
    property string gameresult: configController.getVideoFileInAppDir("gameresult.mp4");
    property string superGameResult: configController.getVideoFileInAppDir("cola.mp4");
    anchors.fill: parent;

    Video
    {
        id: player1;
        anchors.fill: parent;
        anchors.centerIn: parent;
        loops: MediaPlayer.Infinite;
        playlist: Playlist
        {
            id: playlist1;
        }

        OpacityAnimator on opacity
        {
            id:videoAnim1;
            target: player1;
            from: 0;
            to: 1;
            duration: 500;
            running:false;

            onStopped:
            {
                player2.seek(0);
                player2.pause();
                player2.visible = false;
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
        playlist: Playlist
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
            target: player2;

            onStopped:
            {
                player1.seek(0);
                player1.pause();
                player1.visible = false;
            }
        }
    }

    BgParticles
    {
        id: bgParticles;
        z: 1;
        visible: false;

        OpacityAnimator on opacity
        {
            id:particlesAnim;
            from: 0;
            to: 1;
            duration: 500;
            running:false;
            target: bgParticles;

            onStopped:
            {
                if(bgParticles.opacity == 1)
                {
                    currentPlayer.seek(0);
                    currentPlayer.pause();
                    currentPlayer.visible = false;
                }
            }
        }
    }

    Component.onCompleted:
    {
        playlist1.addItem(intro1Path);
        playlist1.addItem(intro2Path);
        playlist1.addItem(instructionPath);
        playlist1.addItem(bgLoop);
        playlist1.addItem(gameresult);
        playlist1.addItem(superGameResult);


        playlist2.addItem(intro1Path);
        playlist2.addItem(intro2Path);
        playlist2.addItem(instructionPath);
        playlist2.addItem(bgLoop);
        playlist2.addItem(gameresult);
        playlist2.addItem(superGameResult);


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

    property bool superGameSuccess: false;

    Connections
    {
        target: superGameModule;

        onSuperGameFailed:
        {
            superGameSuccess = false;
        }

        onSuperGameSuccess:
        {
            superGameSuccess = true;
        }
    }

    function setState(appState)
    {
        //        if(currentState == appState)
        //        {
        //            return;
        //        }

        //console.log("swaaaaaaaaap")

        positionTimer.stop();

        player1.loops = MediaPlayer.Infinite;
        player2.loops = MediaPlayer.Infinite;

        switch(appState)
        {
        case AppState.Intro:
            stopParticles();
            startIndex(0);
            break;

        case AppState.Instruction:
            stopParticles();
            startIndex(2);
            break;

        case AppState.Roulette:
        case AppState.Game:
            startParticles();
            //startIndex(3);
            break;

        case AppState.GameResult:
            stopParticles();
            startIndex(4);
            currentPlayer.loops = 1;
            break;

        case AppState.SuperGame:
            startParticles();
            break;

        case AppState.SuperGameResult:

            if(superGameSuccess)
            {
                stopParticles();
                startIndex(5);
                currentPlayer.loops = 1;
            }
            else
            {
                startParticles();
            }

            break;

        case AppState.TestDrive:
            startParticles();
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
            // console.log("PAUSEEEEEEEEEEEEEEE")
            if (currentPlayer.loops == 1 && (currentPlayer.position > 1000 && currentPlayer.duration - currentPlayer.position < 1000))
            {

                currentPlayer.pause();
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
            currentPlayer = player1;
            currentPlaylist = playlist1;
            currentVideoAnim = videoAnim1;
        }
        else if(currentPlayer == player1)
        {
            currentPlayer = player2;
            currentPlaylist = playlist2;
            currentVideoAnim = videoAnim2;
        }
    }

    function playAnim()
    {
        videoAnim2.stop();
        videoAnim1.stop();

        currentPlayer.visible = true;
        currentPlayer.opacity = 0;
        currentPlayer.z = 1;
        currentVideoAnim.from = 0;
        currentVideoAnim.to = 1;
        currentVideoAnim.start();


        var opposePlayer = getOppositePlayer();
        opposePlayer.z = 0;

        //        var opposePlayerAnim = getOppositePlayerAnim();
        //        opposePlayerAnim.from = 1;
        //        opposePlayerAnim.to = 0;
        //        opposePlayerAnim.start();

    }

    function stopParticles()
    {
        if(bgParticles.opacity === 1)
        {
            particlesAnim.from = 1;
            particlesAnim.to = 0;
            particlesAnim.start();
        }
    }

    function startParticles()
    {
        videoAnim2.stop();
        videoAnim1.stop();

        bgParticles.visible = true;
        bgParticles.opacity = 0;
        bgParticles.z = 1;

        particlesAnim.from = 0;
        particlesAnim.to = 1;
        particlesAnim.start();

        currentPlayer.z = 0;
        currentVideoAnim.from = 1;
        currentVideoAnim.to = 0;
        currentVideoAnim.start();

    }

    function getOppositePlayer()
    {
        return  currentPlayer == player1 ? player2 : player1;
    }

    function getOppositePlayerAnim()
    {
        return  currentPlayer == player1 ? videoAnim2 : videoAnim1;
    }


}
