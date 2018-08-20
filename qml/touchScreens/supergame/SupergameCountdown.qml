import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

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
        id: tools;
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
        antialiasing: true;
        rotation: -90;

        property int centerWidth: 1080 * 0.5
        property int centerHeight: 1920 * 0.5
        property int radius: 400;

        property real percentLimit: 0.0;
        property real percent: 0.5;

        onPercentChanged: requestPaint();

        onPaint:
        {
            var colorAttention= Qt.rgba(255.0 / 255., 255./255., 255.0 / 255., 0.2);
            var colorBg = Qt.rgba(10./255., 171./255., 212.0 / 255., 1.0);

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
                    canvasCirc.radius, 0, 2 * Math.PI * percent );//
            //  2 * Math.PI * percent, 0);
            ctx.stroke();
            ctx.closePath();
        }

        PropertyAnimation
        {
            id: roundAnim;
            target: canvasCirc;
            property: "percent";
            from:1;
           // to: 0;
            duration: 2000
        }

        FastBlur
        {
            anchors.fill: canvasCirc
            source: canvasCirc
            radius: 50
            //transparentBorder:true;
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
        horizontalAlignment: Text.AlignHCenter;
        text: "00:00";

        Text
        {
            id: minutesText2;
            anchors.horizontalCenter: minutesText.horizontalCenter;
            anchors.top: minutesText.bottom;
            anchors.topMargin: -10;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 30 * consts.designScale;
            text: "ОСТАЛОСЬ";
            color: "#0aabd4";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 2000;
        running: false;
        easing.type: "InOutCubic";
    }

    ScaleAnimator on scale
    {
        id: scaleAnim;
        from: 0.3;
        to: 1;
        duration: 1000;
        running: false;
        easing.type: "InOutCubic";
    }

    Connections
    {
        target: superGameModule;
        onUpdateSuperGameTime:
        {
            var seconds = (mills / 1000.).toFixed(0);
            minutesText.text = tools.formatSeconds(seconds);

           // roundAnim.duration = 100;
           // roundAnim.to =
           // console.log(1000 *seconds/superGameModule.getSuperGameTime())
            //roundAnim.start();
            canvasCirc.percent = 1000 * seconds/superGameModule.getSuperGameTime();
        }

        onSuperGameFailed:
        {
            //console.log("SuperGameFailed");
        }

        onSuperGameSuccess:
        {
          //  console.log("onSuperGameSuccess");
        }
    }

    function show()
    {
        // roundAnim.duration = superGameModule.getSuperGameTime();
        // roundAnim.start();

        canvasCirc.percent  = 1;
        canvasCirc.requestPaint();
        opacity = 0;
        scale = 0.3;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
        scaleAnim.start();
    }

    function hide()
    {
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.start();
        scaleAnim.stop();
    }
}
