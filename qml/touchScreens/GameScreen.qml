import QtQuick 2.2
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import "advantages"
import "../components"
import ".."

Item
{
    id:gameScreen;
    anchors.fill: parent;

    property string mainTitleDefault: "Концентрируйся<br/>на Santa fe.<br/>Двигайся к точке.";

    signal animComplete();
    signal animStart();

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }


//    Video
//    {
//        id: video;
//        width: parent.width;
//        height: parent.height;
//        loops: MediaPlayer.Infinite;
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.verticalCenter: parent.verticalCenter;
//        focus: true;
//        autoLoad:false;
//    }

    Text
    {
        id: mainText;
        anchors.fill: parent;
        anchors.centerIn: parent;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize:  90 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        opacity: 0;

        OpacityAnimator on opacity
        {
            id: opacityAnim;
            from: 0;
            to: 1;
            duration: 700;
            running:false;
            easing.type: "InOutCubic";
        }


        ScaleAnimator on scale
        {
            id: scaleAnim;
            from: 0.5;
            to: 1;
            duration: 700;
            running:false;
            easing.type: "InOutCubic";
        }
    }

    AdvantageDescription
    {
        id:advatage;

        onAdvantageReaded:
        {
            mainText.visible = true;
            advatage.hide();
            appearAnimation();
            gameModule.continueGame();

        }
    }

//    VideoManager
//    {
//        id: videos;
//    }

    Component.onCompleted:
    {
       // video.source = videos.bgLoop;
    }

    Connections
    {
        target: gameModule;

        onStageComleteEvent:
        {
            mainText.visible = false;
            advatage.setTexts(title, description);
            advatage.setVideo(videoPath);
            advatage.show();
        }
    }

    function start()
    {
        visible = true;
        gameScreen.animComplete();
       // video.seek(0);
      //  video.play();
        appearAnimation();
    }

    function appearAnimation()
    {
        mainText.opacity = 0.0;
        mainText.scale = 0.5;
        opacityAnim.start();
        scaleAnim.start();
    }

    function stop()
    {
        visible = false;
        mainText.visible = true;
        mainText.opacity = 0.0;
        mainText.scale = 0.5;
       // video.stop();
        advatage.hide();
    }
}
