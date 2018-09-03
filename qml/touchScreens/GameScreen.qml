import QtQuick 2.2
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import "game"
import "../tools"

Item
{
    id: gameScreen;

    property string mainTitleDefault: "Думайте о новом<br/>Hyundai SANTA FE.<br/><br/>Чем выше концентрация —<br/>тем выше скорость.";

    signal animComplete();
    signal animStart();

    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    Text
    {
        id: mainText;
        anchors.fill: parent;
        anchors.centerIn: parent;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize:  60;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        opacity: 0;

        AnimationPlayer
        {
            id: animationItem;
            currentImage: 0;
            endFrame: 35;
            startFrame: 0;

            Component.onCompleted:
            {
                animationItem.setSource("content/misc/arrow/", ".png");
                animationItem.setFPS(30);
                animationItem.setRunning(false);
                animationItem.setLocation((1080 - 200) * 0.5, (1920 - 200) * 0.5 - 300);
                animationItem.init();
            }
        }

        OpacityAnimator on opacity
        {
            id: opacityAnim;
            from: 0;
            to: 1;
            duration: 700;
            running: false;
            easing.type: "InOutCubic";
        }

        ScaleAnimator on scale
        {
            id: scaleAnim;
            from: 0.5;
            to: 1;
            duration: 700;
            running:false;
            easing.type: "OutCubic";
        }
    }

    AdvantageDescription
    {
        id:advatage;

        onAdvantageReaded:
        {
            advatage.hide();
            hideAdvantageTimer.start();
        }
    }

    Timer
    {
        id:hideAdvantageTimer;
        interval: 1500;
        running: false;
        onTriggered:
        {
            hideAdvantageTimer.stop();
            appearAnimation();
            gameModule.continueGame();
        }
    }

    Connections
    {
        target: gameModule;

        onStageComleteEvent:
        {
            stageCompleted(title, description, videoPath);
        }
    }

    function stageCompleted(title, description, videoPath)
    {
        mainText.visible = false;
        advatage.visible = true;
        advatage.setTexts(title, description);
        advatage.setVideo(videoPath);
        advatage.visible = true;
        advatage.show();
    }

    function start()
    {
        visible = true;
        gameScreen.animComplete();
        appearAnimation();
    }

    function appearAnimation()
    {
        mainText.visible = true;
        mainText.opacity = 0.0;
        mainText.scale = 0.5;
        opacityAnim.start();
        scaleAnim.start();
    }

    function stop()
    {
        advatage.visible = false;
        hideAdvantageTimer.stop();
        visible = false;
        mainText.visible = true;
        mainText.opacity = 0.0;
        mainText.scale = 0.5;
        advatage.visible = false;
    }
}
