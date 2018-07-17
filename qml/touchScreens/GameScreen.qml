import QtQuick 2.0
import QtQuick.Controls 2.2
import "elements"

Item
{
    anchors.fill: parent;

    property string mainTitleDefault: "КОНЦЕНТРИРУЙСЯ<br/>НА SANTA FE.<br/>ДВИГАЙСЯ К ТОЧКЕ";

    Text
    {
        id:mainText;
        anchors.fill: parent;
        anchors.centerIn: parent;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        verticalAlignment :Text.AlignVCenter;
    }

    AdvantageDescription
    {
        id:advatage;

        onAdvantageReaded:
        {
            mainText.visible = true;
            advatage.visible = false;
            gameModule.continueGame();
        }
    }

    Connections
    {
        target:gameModule;
        onTaskComleteEvent:
        {
            mainText.visible = false;
            advatage.visible = true;
        }
    }

    function stop()
    {
        mainText.visible = true;
        advatage.visible = false;
    }
}
