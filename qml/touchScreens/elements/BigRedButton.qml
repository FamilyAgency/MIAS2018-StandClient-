import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../../tools"

Item
{
    id: core;

    signal clicked;

    anchors.fill: parent;

    property alias btnWidth:  bg.implicitWidth;
    property alias btnHeight:  bg.implicitHeight;
    property alias btnRadius:  bg.radius;

    FontManager
    {
        id: font;
    }

    Item
    {
        anchors.fill: parent;

        Button
        {
            id: startBtn;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;

            background: Rectangle
            {
                id: bg;
               // implicitHeight: core.btnWidth
              //  implicitWidth: core.btnWidth;
                color: startBtn.down ? "#f00000" : "#fb0000";
               // radius: core.btnWidthHalf;
            }

            contentItem: Text
            {
                id: content;
                z: 1;
                font.family: font.hyundaiSansHeadMedium;
                font.pixelSize: 30 * consts.designScale;
                color: "#ffffff";
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }

            onClicked:
            {
                core.clicked();
            }

            Glow
            {
                id: glow;
                anchors.fill: bg;
                radius: 20;
                samples: 50;
                color: "#fb0000";
                source: bg;
                spread: 0.3;
                opacity: 0;

                OpacityAnimator on opacity
                {
                    id:glowOpacty;
                    from: 0;
                    to: 1;
                    running:false;
                    duration: 500;
                    easing.type: "InOutQuad";
                }
            }
        }

        ScaleAnimator
        {
            id:scaleAnimator;
            target: startBtn;
            from: 0;
            to: 1;
            duration: 500
            running: false;
            easing.type: "InOutQuad";
        }
    }

//    function setWidth(width)
//    {
//        bg.implicitHeight = width * consts.designScale;
//        bg.implicitWidth = width * consts.designScale;
//        bg.radius = (width / 2) * consts.designScale;
//    }

    function setTitle(title)
    {
        content.text = title;
    }

    function show()
    {
        visible = true;

        scaleAnimator.from = 0;
        scaleAnimator.to = 1;
        scaleAnimator.start();

        glow.opacity = 0;
        glowOpacty.from = 0;
        glowOpacty.to = 1;
        glowOpacty.start();
    }

    function hide()
    {
        //visible = false;
        scaleAnimator.from = 1;
        scaleAnimator.to = 0.0;
        scaleAnimator.start();

        glowOpacty.from = 1;
        glowOpacty.to = 0;
        glowOpacty.start();
    }
}
