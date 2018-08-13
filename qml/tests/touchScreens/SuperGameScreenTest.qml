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
        anchors.topMargin: 500;
        anchors.left: parent.left;

        contentItem: Text
        {
            text: "ПРОЙТИ СУПЕРИГРУ";
            font.family: "Helvetica";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            implicitWidth: 200;
            color: "#ffffff";
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
