import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: result;

    property string mainTitleDefault: "ПОЛУЧИТЕ<br/>НАПИТОК.<br/>ПОПРОБУЙТЕ СЫГРАТЬ<br/>В СУПЕР ИГРУ<br/>ЧЕРЕЗ 20 МИНУТ.";
    property string buttonText: "ЗАБРАТЬ ПОДАРОК";

    anchors.fill: parent;
    anchors.centerIn: parent;

    Text
    {
        id:mainTitle;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }
}
