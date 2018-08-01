import QtQuick 2.0

Item
{
    id: testDrive;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "ТЕСТ ДРАЙВ";

    signal animComplete();
    signal animStart();

    Text
    {
        id: mainText;
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

    function start()
    {
        visible = true;
        testDrive.animComplete();
    }

    function stop()
    {
        visible = false;
    }
}
