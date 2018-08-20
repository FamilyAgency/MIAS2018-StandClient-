import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../../tools"

Item
{
    id: bigRedButton;
    anchors.fill: parent;

    signal clicked;

    property alias btnWidth: bg.implicitWidth;
    property alias btnHeight: bg.implicitHeight;
    property alias btnRadius: bg.radius;

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
            enabled: false;
            //anchors.top: parent.top;

            background: Rectangle
            {
                id: bg;
                color: "#66d5fc";
                opacity: startBtn.down ? 0.95 : 1;
                border.width: 0;

                gradient: Gradient
                {
                    GradientStop
                    {
                        position: 0.0
                        SequentialAnimation on color
                        {
                            loops: Animation.Infinite
                            ColorAnimation { from: "#0b9abf"; to: "#66d5fc"; duration: 3500 }
                            ColorAnimation { from: "#66d5fc"; to: "#0b9abf"; duration: 2500 }
                        }
                    }
                    GradientStop
                    {
                        position: 1.0
                        SequentialAnimation on color
                        {
                            loops: Animation.Infinite
                            ColorAnimation { from: "#0aabd4"; to: "#006c92"; duration: 2500 }
                            ColorAnimation { from: "#006c92"; to: "#0aabd4"; duration: 3500 }
                        }
                    }
                }
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
                bigRedButton.clicked();
            }

            Glow
            {
                id: glow;
                anchors.fill: bg;
                radius: 40;
                samples: 150;
                color: "#66d5fc";
                source: bg;
                spread: 0.1;
                opacity: 0;

                OpacityAnimator on opacity
                {
                    id:glowOpacty;
                    from: 0;
                    to: 0.3;
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
            onStopped:
            {
                if(startBtn.scale == 1)
                {
                    startBtn.enabled = true;
                }
            }
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
        console.log(" show--------------");


        startBtn.scale = 0;

        scaleAnimator.from = 0;
        scaleAnimator.to = 1;
        scaleAnimator.start();

        glow.opacity = 0;
        glowOpacty.from = 0;
        glowOpacty.to = 0.6;
        glowOpacty.start();
    }

    function hide()
    {
       // visible = false;
        startBtn.enabled = false;
        scaleAnimator.from = 1;
        scaleAnimator.to = 0.0;
        scaleAnimator.start();

        glowOpacty.from = 1;
        glowOpacty.to = 0;
        glowOpacty.start();
    }
}
