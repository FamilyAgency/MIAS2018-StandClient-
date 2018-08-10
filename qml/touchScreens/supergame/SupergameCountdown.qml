import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../../tools"

Item
{
    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    Tools
    {
        id:tools;
    }

    Consts
    {
        id: consts;
    }

    Canvas
    {
        id: canvasCirc;
        width: 1080;
        height: 1920;
        smooth: true;
        antialiasing:true;
        property int centerWidth: 1080 * 0.5
        property int centerHeight: 1920 * 0.5
        property int radius: 400;

        property real percentLimit: 0.0;
        property real percent: 0.5;

        onPaint:
        {
            var colorAttention= Qt.rgba(255.0 / 255., 255./255., 255.0 / 255., 0.2);
            var colorBg = Qt.rgba(51./255., 106./255., 238.0 / 255., 1.0);

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, 1080, 1920);

            ctx.strokeStyle = consts.redColor;
            ctx.lineCap = consts.lineCap;
            ctx.lineJoin = consts.lineJoin;

            ctx.lineWidth = 1;

            ctx.strokeStyle = colorAttention;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2 * Math.PI);
            ctx.stroke();
            ctx.closePath();

            ctx.lineWidth = 5;
            ctx.strokeStyle = colorBg;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    2 * Math.PI * percent, 0);
            ctx.stroke();
            ctx.closePath();
        }

        PropertyAnimation
        {
            id: attentionAnim;
            target: canvasCirc;
            property: "percentAttention";
            to: 100;
            duration: 50
        }
    }

    Image
    {
        id: time
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -160;
        smooth: true;
        source: "qrc:/resources/time_round.png"
        width: 81 * consts.designScale;
        height: 81 * consts.designScale;
    }

    Text
    {
        id: minutesText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 160 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        text: "00:99";

        Text
        {
            id: minutesText2;
            anchors.horizontalCenter: minutesText.horizontalCenter;
            anchors.top: minutesText.bottom;
            anchors.topMargin: -10;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 30 * consts.designScale;
            text: "ОСТАЛОСЬ";
            color: "#336aee";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
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

    Connections
    {
        target: superGameModule;
        onUpdateSuperGameTime:
        {
            var seconds = (mills / 1000.).toFixed(0);
            canvasCirc.percent  = (1 - superGameModule.getPercent()).toFixed(2);
            canvasCirc.requestPaint();
            minutesText.text = tools.formatSeconds(seconds);
        }

        onSuperGameFailed:
        {
            console.log("SuperGameFailed");
        }

        onSuperGameSuccess:
        {
            console.log("onSuperGameSuccess");
        }
    }

    function show()
    {
        canvasCirc.percent  = 1;
        canvasCirc.requestPaint();
        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
    }

    function hide()
    {
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.start();
    }

}
