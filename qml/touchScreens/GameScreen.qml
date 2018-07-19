import QtQuick 2.0
import QtQuick.Controls 2.2
import "advantages"

Item
{
    anchors.fill: parent;

    property string mainTitleDefault: "КОНЦЕНТРИРУЙСЯ<br/>НА SANTA FE.<br/>ДВИГАЙСЯ К ТОЧКЕ";

    Text
    {
        id: mainText;
        anchors.fill: parent;
        anchors.centerIn: parent;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    AdvantageDescription
    {
        id:advatage;

        onAdvantageReaded:
        {
            mainText.visible = true;
            advatage.hide();
            gameModule.continueGame();
        }
    }

    Connections
    {
        target:gameModule;
        onTaskComleteEvent:
        {
            mainText.visible = false;           
            advatage.setTexts(title, description);
            advatage.setVideo(videoPath);
            advatage.show();
        }
    }

    function stop()
    {
        mainText.visible = true;
         advatage.hide();
    }
}
