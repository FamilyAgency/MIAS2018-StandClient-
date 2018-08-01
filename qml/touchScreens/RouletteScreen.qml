import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{    
    id:roulette;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "РУЛЕТКА ПОМОЖЕТ ВЫБРАТЬ МАРШРУТ<br/> ВЫХОДНОГО ДНЯ В ГОРОДЕ ВМЕСТЕ С СЕМЬЕЙ<br/>\
В ГОРОДЕ ВМЕСТЕ С СЕМЬЕЙ";

    property string rollTextDefault: "КРУТИ!";
    property int circleSize : 300;
    property double nextAttentionValue: 0.0;

    signal animComplete();
    signal animStart();

    MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            if(rouletteModule.state == RouletteState.Roll)
            {
                rouletteModule.createRollParams(100);
                // console.log("roll");
                // rollAnim.start();
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
            id: rollAnim;
            loops: 1;
            from: 0;
            to: 360 + 90;
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

    Canvas
    {
        id: canvasStatic;
        width: parent.width;
        height: parent.height;
        antialiasing: true;
        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            ctx.lineWidth = 10;
            var triSide = 80;
            var offset = 10;

            //// trianle
            ctx.strokeStyle = "#1c1c1c";
            ctx.fillStyle = "#1c1c1c";
            ctx.beginPath();
            ctx.moveTo(canvas.width * 0.5, canvas.height * 0.5 - circleSize + triSide);
            ctx.lineTo(canvas.width * 0.5 + triSide * 0.5,  canvas.height * 0.5 - circleSize - offset);
            ctx.lineTo(canvas.width * 0.5 - triSide * 0.5, canvas.height * 0.5 - circleSize - offset);
            ctx.fill();
            ////
        }
    }

    Rectangle
    {
        anchors.horizontalCenter: parent.horizontalCenter;
        y: parent.height + rouletteModule.carY;
        width: 150;
        height: rouletteModule.carHeight;
        color: "#cdcdcd";
        radius: 10;
    }

    Text
    {
        id: mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: rollText;
        visible:true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenterOffset: circleSize + 50;
        text: rollTextDefault;
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: taskText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: userData.gameUserData.description;
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: helpText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenterOffset: circleSize + 60;
        text: "А ТЕПЕРЬ ТЕБЕ НУЖНО<br/>КОНЦЕНТРИРОВАТЬСЯ<br/>НА АВТОМОБИЛЕ.<br/>ПОЕХАЛИ!";
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        OpacityAnimator on opacity
        {
            id:hintOpactyAnimator;
            from: 0;
            to: 1;
            running:false;
            duration: 500
        }
    }

    RowLayout
    {
        id: mindwaveVisual;
        spacing: 6;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
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
            opacity: 0.2;
            value: 0.0;
            style: ProgressBarStyle
            {
                background: Rectangle
                {
                    radius: 2;
                    color: "lightgray";
                    border.color: "gray";
                    border.width: 1;
                    implicitWidth: 300;
                    implicitHeight: 24;
                }

                progress: Rectangle
                {
                    color: "#990000";
                    border.color: "steelblue";
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
        target: rouletteModule;

        onStateChanged:
        {
            console.log(":::::::::::: state changed::::::::::::", rouletteModule.state)
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
                roulette.animComplete();
                break;

            case RouletteState.RollFinished:
                rollText.visible = false;
                mainText.visible = false;
                taskText.visible = true;
                helpText.visible = false;
                mindwaveVisual.visible = false;
                roulette.animStart();
                break;

            case RouletteState.CarStarting:
                rollText.visible = false;
                mainText.visible = false;
                taskText.visible = true;
                helpText.opacity = 0;
                helpText.visible = true;
                hintOpactyAnimator.start();
                mindwaveVisual.visible = true;
                break;
            }
        }

        onRollParamsUpdate:
        {
            rollAnim.to = degrees;
            rollAnim.start();
            roulette.animStart();
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
        visible = true;
    }

    function stop()
    {
        visible = false;

        rollAnim.stop();
        canvas.rotation = 0;
        rollText.visible = false;
        mainText.visible = true;
        taskText.visible = false;
        helpText.visible = false;
        mindwaveVisual.visible = false;
    }
}
