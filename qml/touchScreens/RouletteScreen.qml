import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{    
    id:roulette;
    anchors.fill: parent;
    anchors.centerIn: parent;

    property double nextAttentionValue: 0.0;

    MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            if(rouletteModule.state == RouletteState.Roll)
            {
                rollAnim.start();
            }
        }
    }

    Canvas
    {
        id: canvas;
        width: parent.width;
        height: parent.height;
        antialiasing: true;

        RotationAnimation on rotation
        {
            id:rollAnim;
            loops: 1;
            from: 0;
            to: 360;
            duration: 2000;
            running: false;
            easing.type: "InOutCubic"

            onStopped:
            {
                if(rouletteModule.state == RouletteState.Roll)
                {
                    rouletteModule.state = (RouletteState.RollFinished);
                }
            }
        }

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

            if(rouletteModule.state != RouletteState.CarStarting)
            {
                ctx.strokeStyle = "#999999";
                ctx.fillStyle = "#999999";
                ctx.beginPath();
                ctx.arc(canvas.width * 0.5, canvas.height * 0.5 - 200, 20, 0, 2*Math.PI);
                ctx.stroke();
                ctx.fill();
            }
        }
    }

    Rectangle
    {
        anchors.horizontalCenter: parent.horizontalCenter;
        y: parent.height + rouletteModule.carY;
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
        id:taskText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "НА ПИКНИК<br/>В ПАРК СОКОЛЬНИКИ";
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#999999";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:helpText;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "А ТЕПЕРЬ ТЕБЕ НУЖНО<br/>КОНЦЕНТРИРОВАТЬСЯ<br/>НА АВТОМОБИЛЕ.<br/>ПОЕХАЛИ!";
        font.family: "Helvetica";
        font.pixelSize: 35;
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

    RowLayout
    {
        id:mindwaveVisual
        spacing: 6;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        visible:false;

        Text
        {
            text: "Attention";
            Layout.alignment : Qt.AlignHCenter;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#990000"
        }

        ProgressBar
        {
            id: attentionProgressBar;
            opacity: 0.2
            value: 0.0;
            style: ProgressBarStyle
            {
                background: Rectangle
                {
                    radius: 2
                    color: "lightgray"
                    border.color: "gray"
                    border.width: 1
                    implicitWidth: 300
                    implicitHeight: 24
                }

                progress: Rectangle
                {
                    color:  "#990000"
                    border.color: "steelblue"
                }
            }
        }

        PropertyAnimation
        {
            id: attentionAnim;
            target: attentionProgressBar;
            property: "value";
            to: 100;
            duration: 500
        }
    }

    Connections
    {
        target:rouletteModule;
        onStateChanged:
        {
            console.log(":::::::::::: state changed::::::::::::", rouletteModule.state )
            canvas.requestPaint();

            switch(rouletteModule.state)
            {
            case RouletteState.Intro:
                rollText.visible = false;
                mainText.visible = true;
                taskText.visible = false;
                helpText.visible = false;
                mindwaveVisual.visible = false;
                break;

            case RouletteState.Roll:
                rollText.visible = true;
                mainText.visible = true;
                taskText.visible = false;
                helpText.visible = false;
                mindwaveVisual.visible = false;
                break;

            case RouletteState.RollFinished:
                rollText.visible = false;
                mainText.visible = false;
                taskText.visible = true;
                helpText.visible = false;
                mindwaveVisual.visible = false;
                break;

            case RouletteState.CarStarting:
                rollText.visible = false;
                mainText.visible = false;
                taskText.visible = true;
                helpText.visible = true;
                mindwaveVisual.visible = true;
                break;
            }
        }

        onLocationStopped:
        {
            rollAnim.stop();
            canvas.rotation = 0;
        }
    }

    Connections
    {
        target:mind;
        onAttentionChanged:
        {
            if(rouletteModule.state == RouletteState.CarStarting)
            {
                nextAttentionValue = mind.attention / 100.0;
                attentionAnim.to = nextAttentionValue;
                attentionAnim.duration = 1000;
                attentionAnim.start();
            }
        }

        onMeditationChanged:
        {

        }

        onPoorSignalLevelChanged:
        {

        }
    }

    function start()
    {

    }

    function stop()
    {
        rollAnim.stop();
        canvas.rotation = 0;
    }
}
