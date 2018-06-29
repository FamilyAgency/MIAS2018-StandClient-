import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent

    function reset()
    {

    }

    Rectangle
    {
        anchors.fill: parent
        color: "white"
        width: 400;
        height: 400;

        Image
        {
            id:heart;
            anchors.centerIn: parent
            source:"qrc:/resources/heart.png"
        }

        Text
        {
            id:mainText;
            anchors.centerIn: parent
            text: "Game " +  gameProgress.currentGameId
            font.family: "Helvetica"
            font.pixelSize: 25
            color: "#ffffff"
        }

        Button
        {
            text: "Finish game"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: mainText.bottom
            onClicked:
            {
                 appController.startResult();
            }
        }
    }
}
