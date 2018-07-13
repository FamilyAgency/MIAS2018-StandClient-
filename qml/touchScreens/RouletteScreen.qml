import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{
    id:roulette;
    anchors.fill: parent;
    anchors.centerIn: parent;

    Canvas
    {
        id: canvas;
        width: parent.width;
        height: parent.height;
        antialiasing: true;

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            ctx.lineWidth = 10;
            ctx.strokeStyle = "#8009fb";
            ctx.fillStyle = "#8009fb";
            ctx.beginPath();
            ctx.arc(canvas.width * 0.5, canvas.height * 0.5, 300, 0, 2*Math.PI);
            ctx.stroke();
            ctx.fill();
        }
    }

    Rectangle
    {
        anchors.horizontalCenter: parent.horizontalCenter;
        y:parent.height + rouletteModule.carY;
        width: 100
        height: 100
        color: "red"
        radius: 10
    }

    Text
    {
        id:mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "РУЛЕТКА ПОМОЖЕТ ВЫБРАТЬ МАРШРУТ<br/> ВЫХОДНОГО ДНЯ В ГОРОДЕ ВМЕСТЕ С СЕМЬЕЙ";
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#999999";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:rollText;
        visible:true;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "КРУТИ";
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#999999";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Connections
    {
        target:rouletteModule;
        onRouletteStateChanged:
        {
            console.log("ssssssssssssssssssssssss", state)
            switch(state)
            {
            case RouletteState.Intro:
                rollText.visible = false;
                break;

            case RouletteState.Roll:
                rollText.visible = true;
                break;
            }
        }
    }
}
