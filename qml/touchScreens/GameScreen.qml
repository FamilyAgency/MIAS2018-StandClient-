import QtQuick 2.0
import QtQuick.Controls 2.2
import "elements"

Item
{
    anchors.fill: parent;

    Rectangle
    {
        anchors.fill: parent;
        anchors.centerIn: parent;
        color: "white"

        //        Image
        //        {
        //            id: heart;
        //            anchors.centerIn: parent;
        //            source:"qrc:/resources/heart.png";
        //        }

        Text
        {
            id:promtText;
            anchors.fill: parent;
            anchors.centerIn: parent;
            //Layout.alignment : Qt.AlignHCenter;
            text: "КОНЦЕНТРИРУЙСЯ<br/>НА SANTA FE.<br/>ДВИГАЙСЯ К ТОЧКЕ";
            font.family: "Helvetica";
            font.pixelSize: 55;
            color: "#999999";
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            verticalAlignment :Text.AlignVCenter;
        }

        AdvantageDescription
        {
            id:advatage;

            onAdvantageReaded:
            {
                promtText.visible = true;
                advatage.visible = false;
                gameModule.continueGame();
            }
        }

        //        Text
        //        {
        //            id: mainText;
        //            anchors.centerIn: parent;
        //            text: "Game " + userData.currentGameId;
        //            font.family: "Helvetica";
        //            font.pixelSize: 25
        //            color: "#ffffff";
        //        }

        //        Button
        //        {
        //            text: "Finish game"
        //            anchors.horizontalCenter: parent.horizontalCenter;
        //            anchors.top: mainText.bottom;
        //            onClicked:
        //            {
        //                 appController.startResult();
        //            }
        //        }
    }

    Connections
    {
        target:gameModule;
        onTaskComleteEvent:
        {
            promtText.visible = false;
            advatage.visible = true;
        }
    }

    function stop()
    {
        promtText.visible = true;
        advatage.visible = false;
    }
}
