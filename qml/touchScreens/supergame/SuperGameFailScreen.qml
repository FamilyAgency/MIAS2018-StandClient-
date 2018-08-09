import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: result;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "ПОЛУЧИТЕ<br/>НАПИТОК.<br/>ПОПРОБУЙТЕ СЫГРАТЬ<br/>В СУПЕР ИГРУ<br/>ЧЕРЕЗ 20 МИНУТ.";
    property string buttonText: "ЗАБРАТЬ ПОДАРОК";

    signal gotoIntro();

    Text
    {
        id: mainTitle;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Button
    {
        id: failOkBtn;

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
            color: failOkBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            result.gotoIntro();
        }
    }
}
