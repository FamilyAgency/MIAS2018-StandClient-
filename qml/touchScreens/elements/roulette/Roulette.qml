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
        rotation: rouletteModule.rotation;
        visible: rouletteModule.particlesVisibility;
    }

    Rectangle
    {
        id:bgPulsar;
        implicitHeight: 1200 * consts.designScale;
        implicitWidth: 1200 * consts.designScale;

        color:  "#7b7cfe"//"#7b7cfe";
        radius: 600 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        scale: rouletteModule.pulsarScale;
        opacity: 1 - rouletteModule.pulsarScale;
    }

    Rectangle
    {
        id:bg;
        implicitHeight: 950 * consts.designScale;
        implicitWidth: 950 * consts.designScale;

        color:  "#7b7cfe";
        radius: 475 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        scale: rouletteModule.scale;
    }

    Canvas
    {
        id: canvas;
        width: parent.width;
        height: parent.height;
        antialiasing: true;
        visible:false;

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
                break;

            case RouletteState.Roll:
                break;

            case RouletteState.RollFinished:
                break;

            case RouletteState.CarStarting:
                break;
            }
        }
    }

}
