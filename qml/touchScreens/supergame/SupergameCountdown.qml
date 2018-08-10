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
        property real percentAttention: 0.5;

        onPaint:
        {
            var colorBg = Qt.rgba(0., 164./255., 227.0 / 255., 0.3);
            var colorLimit =  Qt.rgba(255./255.,52./255., 12./255., 1.);
            var colorAttention = Qt.rgba(159./255., 217./255., 239.0 / 255., 0.9);
            var lineWidth = 4;

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, 250, 250);

            ctx.strokeStyle = consts.redColor;
            ctx.lineCap = consts.lineCap;
            ctx.lineJoin = consts.lineJoin;

            ctx.lineWidth = lineWidth;

            ctx.strokeStyle = colorBg;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2 * Math.PI);
            ctx.stroke();
            ctx.closePath();

//            ctx.strokeStyle = colorLimit;
//            ctx.beginPath();
//            ctx.arc(canvasCirc.centerWidth,
//                    canvasCirc.centerHeight,
//                    canvasCirc.radius,
//                    0,
//                    2*Math.PI * canvasCirc.percentLimit);
//            ctx.stroke();
//            ctx.closePath();

            var col = colorAttention;
            if(canvasCirc.percentAttention > canvasCirc.percentLimit )
            {
                col = colorLimit;
            }
            else
            {
                col = colorAttention;
            }

            ctx.strokeStyle = col;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2 * Math.PI * canvasCirc.percentAttention);
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

    Text
    {
        id: minutesText;
       // anchors.top: parent.top;
       // anchors.topMargin: 100 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 120 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        text: "00:99";
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
            var minutes = (mills/1000.).toFixed(1);
            canvasCirc.percentAttention = minutes / 20.0;
            canvasCirc.requestPaint();
            minutesText.text =  minutes + "<br/>МИНУТЫ";
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
