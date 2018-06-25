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
        Text
        {
            id:mainText;
            anchors.centerIn: parent
            text: "Game 1";
            font.family: "Helvetica"
            font.pixelSize: 25
            color: "#999999"
        }

        Button
        {
            text: "Fin"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: mainText.bottom
            onClicked:
            {
                 appController.startResult();
            }
        }
    }
}
