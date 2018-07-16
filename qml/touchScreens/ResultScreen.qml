import QtQuick 2.0

Item
{
    anchors.fill: parent

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
            text: "Result screen";
            font.family: "Helvetica"
            font.pixelSize: 25
            color: "#999999"
        }
    }

    function stop()
    {

    }
}
