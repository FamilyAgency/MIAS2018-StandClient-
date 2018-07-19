import QtQuick 2.0
import QtQuick.Controls 2.2
import QtMultimedia 5.8

Item
{
    id:advatage;

    property string mainTitleDefault: "НАЗВАНИЕ<br/>ПРЕИМУЩЕСТВА";
    property int circleSize : 150;
    property string buttonText: "ДАЛЕЕ";

    signal advantageReaded;

    anchors.fill: parent;

    Video
    {
        id: video
        width : 1080;
        height : 600;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
    }

    Text
    {
        id:promtText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -200;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    //Video
    //{

    //}

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
            ctx.arc(canvas.width * 0.5, canvas.height  , circleSize, 0, 2*Math.PI);
            ctx.stroke();
            ctx.fill();
        }
    }

    Button
    {
        //anchors.fill: parent;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 20;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: buttonText;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle
        {
            implicitHeight: 110;
            implicitWidth: 160;
            color: "#801bfc";
            // color: "#990000";
            radius: 10;
        }

        onClicked:
        {
            fullAdvantageDescr.show();
        }
    }

    FullAdvantageDescription
    {
        id: fullAdvantageDescr;

        onAdvantageReaded:
        {
            advatage.advantageReaded();
        }
    }

    function setTexts(title, description)
    {
        //promtText.text = title;
        advatage.mainTitleDefault = title;
        fullAdvantageDescr.setTexts(title, description);
    }

    function show()
    {
        visible = true;
        console.log(configController.getQMLFile("content/video/1.mp4"));
        video.source = configController.getQMLFile("content/video/1.mp4");

        video.play();

        fullAdvantageDescr.hide();
    }

    function hide()
    {
        visible = false;
        fullAdvantageDescr.hide();
    }
}
