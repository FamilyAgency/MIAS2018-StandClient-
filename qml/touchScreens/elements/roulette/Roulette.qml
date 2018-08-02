import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

import "../../../components"
Item
{
    anchors.fill: parent;
    property int circleSize : 300;
    FontManager
    {
        id: font;
    }

    //    Text
    //    {
    //        id: taskText;
    //        anchors.top: parent.top;
    //        anchors.topMargin: 100;
    //        anchors.horizontalCenter: parent.horizontalCenter;
    //        text: userData.gameUserData.description;
    //        font.family: "Helvetica";
    //        font.pixelSize: 35;
    //        color: "#ffffff";
    //        textFormat: Text.StyledText;
    //        horizontalAlignment :Text.AlignHCenter;
    //        visible:false;
    //    }
    Image
    {
        id: roullete
        width: 878 * consts.designScale;
        height: 875  * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 222;
        smooth: true;
        source: "qrc:/resources/rulette.png";

        RotationAnimation on rotation
        {
            id: rollAnim;
            loops: 1;
            from: 0;
            to: 360 + 360;
            duration: 2000;
            running: false;
            easing.type: "InOutCubic";

            onStopped:
            {
                if(rouletteModule.state == RouletteState.Roll)
                {
                    rouletteModule.state = (RouletteState.RollFinished);
                }
            }
        }
        Rectangle
        {
            id:bg;
            implicitHeight: 950 * consts.designScale;
            implicitWidth: 950 * consts.designScale;
            color:  "#7b7cfe";
            radius: 475 * consts.designScale;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            scale: 0;
        }
        ScaleAnimator
        {
            id:scaleAnimator;
            target: bg;
            from: 0;
            to: 1;
            duration: 1000
            running: false;
            easing.type: "InOutQuad";
        }
    }

    Canvas
    {
        id: canvas;
        width: parent.width;
        height: parent.height;
        antialiasing: true;
        visible:false



        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            ctx.lineWidth = 10;
            ctx.strokeStyle = "#8009fb";
            ctx.fillStyle = "#8009fb";
            ctx.beginPath();
            ctx.arc(canvas.width * 0.5, canvas.height * 0.5, circleSize, 0, 2*Math.PI);
            ctx.stroke();
            ctx.fill();

            if(rouletteModule.state == RouletteState.Roll)
            {
                ctx.strokeStyle = "#000099";
                ctx.fillStyle = "#000099";
                ctx.beginPath();
                ctx.arc(canvas.width * 0.5, canvas.height * 0.5 + 200, 20, 0, 2*Math.PI);
                ctx.stroke();
                ctx.fill();

                ctx.strokeStyle = "#990000";
                ctx.fillStyle = "#990000";
                ctx.beginPath();
                ctx.arc(canvas.width * 0.5 - 200, canvas.height * 0.5 , 20, 0, 2*Math.PI);
                ctx.stroke();
                ctx.fill();

                ctx.strokeStyle = "#009900";
                ctx.fillStyle = "#009900";
                ctx.beginPath();
                ctx.arc(canvas.width * 0.5 + 200, canvas.height * 0.5 , 20, 0, 2*Math.PI);
                ctx.stroke();
                ctx.fill();
            }
        }
    }

    Connections
    {
        target: rouletteModule;

        onStateChanged:
        {
            console.log(":::::::::::: state changed::::::::::::", rouletteModule.state)
            canvas.requestPaint();

            switch(rouletteModule.state)
            {
            case RouletteState.Intro:
                bg.scale = 0;
                roullete.rotation = 0;
                break;

            case RouletteState.Roll:

                break;

            case RouletteState.RollFinished:

                scaleAnimator.start();
                break;

            case RouletteState.CarStarting:
                //                brb.visible = false;
                //                mainText.visible = false;
                //                taskText.visible = true;
                //                helpText.opacity = 0;
                //                helpText.visible = true;
                //                hintOpactyAnimator.start();
                //                mindwaveVisual.visible = true;
                break;
            }
        }

        onRollParamsUpdate:
        {
            rollAnim.to = degrees;
            rollAnim.start();
        }
    }

}
