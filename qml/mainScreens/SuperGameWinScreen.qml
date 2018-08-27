import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import "../tools"
import "../components"

Item
{
    property string superGameTitle1: "Поздравляем!";
    property string superGameTitle2: "ТВОЙ РЕЗУЛЬТАТ";
    property bool superGameSuccess: false;
    property int offsetY: 0;


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

    DropShadow
    {
        anchors.fill: bg;
        radius: 100.0;
        samples: 50;
        color: "#00b4e2";
        source: bg;
        spread: 0
    }

    Rectangle
    {
        visible: true;
        id: bg;
        //color: blueColor;
        border.width: 0;
        implicitWidth: 900;
        implicitHeight: 900;
        radius: 450;
        smooth: true;
        antialiasing: true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        gradient: Gradient
        {
            GradientStop { position: 1.0; color: "#011025" }
            GradientStop { position: 0.0; color: "#041936" }
        }
    }

//    AnimationPlayer
//    {
//        id: confAnim;
//        currentImage: 1;
//        endFrame: 191;
//        startFrame: 1;
//        Component.onCompleted:
//        {
//            confAnim.setSource("content/misc/confeti/", ".png");
//            confAnim.setFPS(30);
//            confAnim.setRunning(false);
//            confAnim.init();
//        }
//    }

    Text
    {
        id: title;
        text: superGameTitle1;
        y : 600;
        anchors.bottom: superTime.top;
        anchors.bottomMargin: offsetY;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 65;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: superTime;
        text: "1:34";      
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
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
        anchors.topMargin: -30;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 48;
        color: "#00b4e2";
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

    Component.onCompleted:
    {
       // show();
    }

    function show()
    {
        if(superGameSuccess)
        {
            visible = true;
           // confAnim.setRunning(true);
            opacity = 0;
            opacityAnim.start();
        }
    }

    function hide()
    {
        visible = false;        
       // confAnim.setRunning(false);
    }
}
