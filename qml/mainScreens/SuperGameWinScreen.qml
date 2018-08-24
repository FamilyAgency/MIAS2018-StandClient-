import QtQuick 2.2
import QtQuick.Controls.Styles 1.4

import "../tools"
import "../components"

Item
{
    property string superGameTitle1: "Поздравляем!";
    property string superGameTitle2: "ТВОЙ РЕЗУЛЬТАТ";
    property bool superGameSuccess: false;

    anchors.fill: parent;
    anchors.centerIn: parent;
    visible: false;

    FontManager
    {
        id: font;
    }

    Tools
    {
        id: tools;
    }

    Rectangle
    {
        anchors.fill: parent;
        color: "#021025";
        opacity: 0.0;
    }

    AnimationPlayer
    {
        id: confAnim;
        currentImage: 1;
        endFrame: 191;
        startFrame: 1;
        Component.onCompleted:
        {
            confAnim.setSource("content/misc/confeti/", ".png");
            confAnim.setFPS(30);
            confAnim.setRunning(false);
            confAnim.init();
        }
    }

    Text
    {
        id: title;
        text: superGameTitle1;
        y : 600;
        //anchors.top: parent.top;
       // anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 100;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: superTime;
        text: "1:34";
        anchors.top: title.bottom;
        anchors.topMargin: 60;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 270;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: title2;
        text: superGameTitle2;
        anchors.top: superTime.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 54;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
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

    Connections
    {
        target: superGameModule;

        onSuperGameFailed:
        {
            superGameSuccess = false;
        }

        onSuperGameSuccess:
        {
            superTime.text = tools.formatSeconds(Math.floor(time/1000.0));
            superGameSuccess = true;
        }
    }

    function show()
    {
        if(superGameSuccess)
        {
            visible = true;
            confAnim.setRunning(true);
            opacity = 0;
            opacityAnim.start();
        }
    }

    function hide()
    {
        visible = false;        
        confAnim.setRunning(false);
    }
}
