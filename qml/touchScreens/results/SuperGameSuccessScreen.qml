import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: result;

    property string mainTitleDefault: "ТЫ ПРОШЕЛ<br/>СУПЕР ИГРУ!";
    property string buttonText: "ЗАБРАТЬ ПОДАРОК";

    signal gotoIntro();

    anchors.fill: parent;
    anchors.centerIn: parent;

    Text
    {
        id:mainTitle;
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
        id:timeText;
        anchors.top: mainTitle.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "00:00";
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id:addText;
        anchors.top: timeText.bottom;
        anchors.topMargin: 10;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "РЕЗУЛЬТАТ";
        font.family: "Helvetica";
        font.pixelSize: 45;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Button
    {
        id: takePrizeBtn;

        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
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
            color: takePrizeBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            result.gotoIntro();
        }
    }
}
