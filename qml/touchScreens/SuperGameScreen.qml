import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: result;

    property string mainTitleDefault: "СУПЕР ИГРА";
    property string descrTitleDefault: "МАКСИМАЛЬНАЯ<br/>КОНЦЕНТРАЦИЯ<br/>И СКОРОСТЬ!";
    property string buttonText: "ПОЕХАЛИ";
    property string timeTextDefault: "2<br/>МИНУТЫ";
    property string triesTextDefault: "1<br/>ПОПЫТКА";

    anchors.fill: parent;
    anchors.centerIn: parent;

    Text
    {
        id:mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:descrText;
        anchors.top: mainText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: descrTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 50;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:timeText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: timeTextDefault;
        font.family: "Helvetica";
        font.pixelSize: 50;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:triesText;
        anchors.top: timeText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: triesTextDefault;
        font.family: "Helvetica";
        font.pixelSize: 50;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Button
    {
        id: startBtn;

        anchors.top: triesText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: buttonText;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

        }

        background: Rectangle
        {
            implicitHeight: 200;
            implicitWidth: 400;
            color: startBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            superGameModule.startGame();
            startBtn.visible = false;
            mainText.visible = false;
            descrText.visible = false;
            triesText.visible = false;
            passBtn.visible = true;
        }
    }

    Button
    {
        id: passBtn;

        anchors.top: triesText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: "ПРОЙТИ СУПЕРИГРУ";
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

        }

        background: Rectangle
        {
            implicitHeight: 200;
            implicitWidth: 400;
            color: passBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            superGameModule.superGamePassedTest();
        }
    }

    Connections
    {
        target: superGameModule;
        onUpdateSuperGameTime:
        {
            timeText.text = (mills/1000.).toFixed(1);
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

    function stop()
    {
        timeText.text = timeTextDefault;
        startBtn.visible = true;
        mainText.visible = true;
        descrText.visible = true;
        triesText.visible = true;
        passBtn.visible = false;
    }
}
