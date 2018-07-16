import QtQuick 2.0
import QtQuick.Controls 2.2

Item
{
    id:advatage;

    signal advantageReaded;

    anchors.fill: parent;

    Text
    {
        id:promtText;
        anchors.fill: parent;
        anchors.centerIn: parent;
        text: "НАЗВАНИЕ<br/>ПРЕИМУЩЕСТВА";
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#999999";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        verticalAlignment :Text.AlignVCenter;
    }

    //Video
    //{

    //}

    Button
    {
        //anchors.fill: parent;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "ДАЛЕЕ";
        font.family: "Helvetica";
        font.pixelSize: 55;
        onClicked:
        {
            advatage.advantageReaded();
        }
    }

}
