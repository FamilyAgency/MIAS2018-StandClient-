import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtMultimedia 5.8

import "../../../components"
Item
{
    anchors.fill: parent;
    anchors.centerIn: parent;

    Video
    {
        id: video1;
        width: parent.width;
        height: parent.height;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
        autoLoad:false;
        source: videos.intro1Path;
    }

    Video
    {
        id: video2;
        width: parent.width;
        height: parent.height;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
        autoLoad:false;
        source: videos.intro2Path;

        OpacityAnimator on opacity
        {
            id:helloAnim;
            from: 0;
            to: 1;
            duration: 1000
            running:false;

            onRunningChanged:
            {
                if (!helloAnim.running)
                {
                    video1.visible = false;
                   // video1.seek(0);
                  //  video1.pause();
                }
            }
        }
    }

    VideoManager
    {
        id:videos;
    }

    Component.onCompleted:
    {
        video2.source =  videos.intro2Path;
        video1.source =  videos.intro1Path;

         console.log("videos.intro2Path ", videos.intro2Path);
        console.log("videos.intro2Path ", videos.intro1Path);
    }

    function start()
    {
        video1.visible = true;
        video2.visible = false;

        video1.seek(0);
      //  video2.play();
      //  video2.pause();
        video2.opacity = 0;

        video1.play();
    }

    function startHelloState()
    {
        video2.visible = true;
        video2.seek(0);
        video2.play();
        helloAnim.start();
    }

    function stop()
    {
        video1.stop();
        video2.stop();
       // video1.pause();
        video1.visible = false;

       // video2.seek(0);
       // video2.pause();
        video2.visible = false;
    }
}
