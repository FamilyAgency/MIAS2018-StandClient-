import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    anchors.fill: parent;

    Button
    {
        id: passBtn;

        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: "ПРОЙТИ СУПЕРИГРУ";
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            implicitHeight: 100;
            implicitWidth: 200;
            color: passBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            superGameModule.superGamePassedTest();
        }
    }

    function start()
    {
        visible = true;
    }

    function stop()
    {
        visible = false;
    }
}
