import QtQuick 2.0
import QtMultimedia 5.8

import "../../../components"

Item
{
    id: core;
    anchors.fill: parent;

    property int videoState: 0;

    signal videoCompleted;
    signal almostCompleted;

//    Video
//    {
//        id: video;
//        width: parent.width;
//        height: parent.height;
//        loops: MediaPlayer.Infinite;
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.verticalCenter: parent.verticalCenter;
//        focus: true;
//        autoLoad: false;
//    }

    Timer
    {
        id: positionTimer;
        running: false;
        interval: 100;
        repeat: true;
        onTriggered:
        {
            if(videoState == 0)
            {
                if(video.position > 5500)
                {
                    video.seek(0);
                }
            }
            else if(videoState == 1)
            {
                if(video.position >= 4000)
                {
                    core.almostCompleted();
                    videoState = 2;
                }
            }
            else if(videoState == 2)
            {
                if(video.position >= 9000)
                {
                    stop();
                    core.videoCompleted();
                }
            }
        }
    }

//    VideoManager
//    {
//        id: videos;
//    }

    Component.onCompleted:
    {
      //  video.source = videos.instructionPath;
    }

    function signalIsGood()
    {
        if(videoState == 0)
        {
            videoState = 1;
        }
    }

    function start()
    {
        videoState = 0;
        positionTimer.start();
       // video.seek(0);
       // video.play();
    }

    function stop()
    {
        //video.stop();
    }

}

