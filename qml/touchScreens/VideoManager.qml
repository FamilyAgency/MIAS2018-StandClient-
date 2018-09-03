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

    property var currentPlayer: player2;
    property var currentPlaylist: playlist2;

    property bool superGameSuccess: false;
    property int currentIndex: -1;

    anchors.fill: parent;

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

        OpacityAnimator
        {
            id:videoAnim2;
            from: 0;
            to: 1;
            duration: 800;
            running:false;
            target: player2;
        }
    }

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

    Connections
    {
        target:rfid;

        onCardReaderError:
        {
            switch(error)
            {
            case CardReaderError.CardParsing:
                startIndex(1);
                break;
            }
        }
    }

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
            positionTimer.stop();
            player1.loops = MediaPlayer.Infinite;
            player2.loops = MediaPlayer.Infinite;
            startIndex(2);
            currentPlayer.loops = 1;
            positionTimer.start();
        }
    }

    function setState(appState)
    {
        positionTimer.stop();

        player1.loops = MediaPlayer.Infinite;
        player2.loops = MediaPlayer.Infinite;

        switch(appState)
        {
        case AppState.Intro:
            startIndex(0);
            break;

        case AppState.Instruction:
            startIndex(6);
            break;

        case AppState.Roulette:
        case AppState.Game:
        case AppState.SuperGame:
        case AppState.TestDrive:
            startIndex(3);
            break;

        case AppState.GameResult:
            startIndex(4);
            currentPlayer.loops = 1;
            break;

        case AppState.SuperGameResult:
            if(superGameSuccess)
            {
                startIndex(5);
                currentPlayer.loops = 1;
            }
            else
            {
                startIndex(3);
            }

            break;
        }

        positionTimer.start();
    }

    function startIndex(index)
    {
        currentIndex = index;
        swapVideos();
        currentPlaylist.currentIndex = index;
        currentPlayer.seek(0);
        currentPlayer.play();
        playAnim();
    }

    function swapVideos()
    {
        videoAnim2.stop();
        videoAnim1.stop();

        if(currentPlayer == player2)
        {
            currentPlayer = player1;
            currentPlaylist = playlist1;
            changeVideos(videoAnim1, videoAnim2);
        }
        else if(currentPlayer == player1)
        {
            currentPlayer = player2;
            currentPlaylist = playlist2;
            changeVideos(videoAnim2, videoAnim1);
        }
    }

    function changeVideos(v1, v2)
    {
        v1.from = 0;
        v1.to = 1;
        v1.start();

        v2.from = 1;
        v2.to = 0;
        v2.start();
    }

    function playAnim()
    {
        currentPlayer.visible = true;
        currentPlayer.opacity = 0;
        currentPlayer.z = 1;
    }
}
