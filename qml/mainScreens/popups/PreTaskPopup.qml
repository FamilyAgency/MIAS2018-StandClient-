import QtQuick 2.0

Item {
    visible:false

    Connections
    {
        target:gameTaskManager;


        onPreTaskStartEvent:
        {
            visible = true;
        }

        onTaskStartEvent:
        {
            visible = false;
        }

        onPreTaskCoundownUpdate:
        {
            countdownText.text = time.toFixed(0);
        }
    }

    Canvas
    {
        id: canvasPopup;
        width: 300;
        height: 300;
        property var canvasColor:  Qt.rgba(255./255.,52./255., 12./255., 0.6);

        Component.onCompleted:
        {
            canvasPopup.requestPaint();
        }

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = canvasColor;
            ctx.ellipse(0, 0, 300, 300);
            ctx.fill();
        }

        Text
        {
            anchors.centerIn: parent
            id: roundText
            text: "Round " + gameProgress.currentGameId;
            font.family: "Helvetica";
            font.pixelSize: 35;
            color: "#ffffff";
            x: 0;
            y: 0;
        }

        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            id: countdownText
            text: "3";
            font.family: "Helvetica";
            font.pixelSize: 30;
            color: "#ffffff";
            x: 0;
            y: 180;
        }
    }
}
