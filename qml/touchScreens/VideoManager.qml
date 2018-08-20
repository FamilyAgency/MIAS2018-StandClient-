import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtMultimedia 5.8

import "elements"
import "../tests"
import com.app 1.0

Item
{
    property string intro1Path: configController.getVideoFileInAppDir("intro1");
    property string intro2Path: configController.getVideoFileInAppDir("intro2");
    property string instructionPath: configController.getVideoFileInAppDir("instruction");
    property string bgLoop: configController.getVideoFileInAppDir("bgloop");
    property string gameresult: configController.getVideoFileInAppDir("gameresult");
    property string superGameResult: configController.getVideoFileInAppDir("cola");
    property string instruction0Path: configController.getVideoFileInAppDir("girl");

    anchors.fill: parent;

    //    VideoWindow
    //    {
    //        id: video1;
    //    }

    //    VideoWindow
    //    {
    //        id: video2;
    //        x: 540;
    //    }

    //    VideoWindow
    //    {
    //        id: video3;
    //        x: 1080;
    //    }

    //    Component.onCompleted:
    //    {
    //        video1.setSource(intro1Path);
    //        video2.setSource(intro2Path);
    //        video3.setSource(instructionPath);
    //    }

    //        Video
    //        {
    //            id: player1;
    //            anchors.fill: parent;
    //            anchors.centerIn: parent;
    //            fillMode: VideoOutput.PreserveAspectFit
    //            width: 1080;
    //            loops: MediaPlayer.Infinite;
    //            playlist: Playlist
    //            {
    //                id: playlist1;
    //            }
    //        }


    Video
    {
        id: player1;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fillMode: VideoOutput.PreserveAspectFit
        width: 1080;
        loops: MediaPlayer.Infinite;
        playlist: Playlist
        {
            id: playlist1;
        }

        OpacityAnimator
        {
            id:videoAnim1;
            target: player1;
            from: 0;
            to: 1;
            duration: 800;
            running:false;

            onStopped:
            {
              //  player2.seek(0);
              //  player2.pause();
              //  player2.visible = false;
            }
        }

        onStatusChanged:
        {
           // console.log("status ", status);
            if(status == MediaPlayer.Loaded)
            {
               // console.log("MediaPlayer.Loaded");
            }

            if(status == MediaPlayer.Loading)
            {
              //  console.log("MediaPlayer.Loading", player1.source);
            }
        }
    }

    Video
    {
        id: player2;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fillMode: VideoOutput.PreserveAspectFit
        width: 1080;
        opacity: 0;
        loops: MediaPlayer.Infinite;


        playlist: Playlist
        {
            id: playlist2;

        }

        onStatusChanged:
        {
           // console.log("status ", status);

            if(status == MediaPlayer.Loaded)
            {
               // console.log("MediaPlayer.Loaded");
            }

            if(status == MediaPlayer.Loading)
            {
               //  console.log("MediaPlayer.Loading", player2.source);
            }
        }

        OpacityAnimator
        {
            id:videoAnim2;
            from: 0;
            to: 1;
            duration: 800;
            running:false;
            target: player2;

            onStopped:
            {
             //   player1.seek(0);
             //   player1.pause();
              //  player1.visible = false;
            }
        }
    }

//        BgParticles
//        {
//            id: bgParticles;
//            z: 1;
//            visible: true;

//            OpacityAnimator on opacity
//            {
//                id:particlesAnim;
//                from: 0;
//                to: 1;
//                duration: 500;
//                running:false;
//                target: bgParticles;

//                onStopped:
//                {
//                    if(bgParticles.opacity == 1)
//                    {
//                        currentPlayer.seek(0);
//                        currentPlayer.pause();
//                        currentPlayer.visible = false;
//                    }
//                }
//            }
//        }

    Component.onCompleted:
    {
        playlist1.addItem(intro1Path);
        playlist1.addItem(intro2Path);
        playlist1.addItem(instructionPath);
        playlist1.addItem(bgLoop);
        playlist1.addItem(gameresult);
        playlist1.addItem(superGameResult);
        playlist1.addItem(instruction0Path);

        playlist2.addItem(intro1Path);
        playlist2.addItem(intro2Path);
        playlist2.addItem(instructionPath);
        playlist2.addItem(bgLoop);
        playlist2.addItem(gameresult);
        playlist2.addItem(superGameResult);
        playlist2.addItem(instruction0Path);

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

    Connections
    {
        target: instructionModule;
        onMindwaveReady:
        {
            console.log("--------------- onMindwaveReady ---------------");
            positionTimer.stop();
            player1.loops = MediaPlayer.Infinite;
            player2.loops = MediaPlayer.Infinite;
            startIndex(2);
            currentPlayer.loops = 1;
            positionTimer.start();
        }
    }


    function handleEndOfMedia(index)
    {
        // console.log("video index finished ", index);

        if(index === 2)
        {
           // instructionModule.mediaEnded();
        }

        //        if(currentState == AppState.Instruction)
        //        {
        //            instructionModule.mediaEnded();
        //        }
    }


    function setState(appState)
    {
        // return;


        positionTimer.stop();

        player1.loops = MediaPlayer.Infinite;
        player2.loops = MediaPlayer.Infinite;

        switch(appState)
        {
        case AppState.Intro:
            // stopParticles();
            startIndex(0);
            break;

        case AppState.Instruction:
            // stopParticles();
            startIndex(6);
            // currentPlayer.loops = 1;
            break;

        case AppState.Roulette:
        case AppState.Game:
            // startParticles();
            startIndex(3);
            break;

        case AppState.GameResult:
            // stopParticles();
            startIndex(4);
            currentPlayer.loops = 1;
            break;

        case AppState.SuperGame:
            // startParticles();
            startIndex(3);
            break;

        case AppState.SuperGameResult:

            if(superGameSuccess)
            {
                //stopParticles();
                startIndex(5);
                currentPlayer.loops = 1;
            }
            else
            {
                // startParticles();
                startIndex(3);
            }

            break;

        case AppState.TestDrive:
            // startParticles();
            startIndex(3);
            break;

        }
        currentState = appState;
        positionTimer.start();
    }

        property bool needLoop: false;
        property real loopThreshold: 0;
        property int currentIndex: -1;

    Timer
    {
        id: positionTimer;
        running: false;
        interval: 100;
        repeat: true;
        onTriggered:
        {
            if (currentPlayer.loops == 1 && (currentPlayer.position > 1000 && currentPlayer.duration - currentPlayer.position < 1000))
            {
                currentPlayer.pause();
                handleEndOfMedia(currentPlaylist.currentIndex);
            }
        }
    }

    function startIndex(index, seekTo)
    {
        // if(currentIndex !== index)
        {
            /*if (seekTo === undefined)*/ seekTo = 0;
            currentIndex = index;
            swapVideos();
            currentPlaylist.currentIndex = index;
            currentPlayer.seek(seekTo);
            currentPlayer.play();
            playAnim();
        }
        // else
        {
            //currentPlayer.seek(seekTo);
            // currentPlayer.play();
        }
    }

    function swapVideos()
    {
        videoAnim2.stop();
        videoAnim1.stop();

        if(currentPlayer == player2)
        {
            currentPlayer = player1;
            currentPlaylist = playlist1;
            currentVideoAnim = videoAnim1;

            videoAnim1.from = 0;
            videoAnim1.to = 1;
            videoAnim1.start();


            videoAnim2.from = 1;
            videoAnim2.to = 0;
            videoAnim2.start();
        }
        else if(currentPlayer == player1)
        {
            currentPlayer = player2;
            currentPlaylist = playlist2;
            currentVideoAnim = videoAnim2;

            videoAnim1.from = 1;
            videoAnim1.to = 0;
            videoAnim1.start();


            videoAnim2.from = 0;
            videoAnim2.to = 1;
            videoAnim2.start();

        }
    }

    function playAnim()
    {
        currentPlayer.visible = true;
        currentPlayer.opacity = 0;
        currentPlayer.z = 1;
        //        currentVideoAnim.from = 0;
        //        currentVideoAnim.to = 1;
        //        currentVideoAnim.start();


        // var opposePlayer = getOppositePlayer();
        //  opposePlayer.z = 0;

        //        var opposePlayerAnim = getOppositePlayerAnim();
        //        opposePlayerAnim.from = 1;
        //        opposePlayerAnim.to = 0;
        //        opposePlayerAnim.start();

    }

    function stopParticles()
    {

    }

    function startParticles()
    {

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
