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
        anchors.topMargin: 1200;
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
            implicitHeight: 100;
            color: "#ffffff";
        }

        onClicked:
        {
            superGameModule.superGamePassedTest();
        }
    }


    Button
    {
        id: failBtn;

        anchors.top: parent.top;
        anchors.topMargin: 1400;
        anchors.left: parent.left;

        contentItem: Text
        {
            text: "ПРОИГРАТЬ СУПЕРИГРУ";
            font.family: "Helvetica";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            implicitWidth: 200;
            implicitHeight: 100;
            color: "#ffffff";
        }

        onClicked:
        {
            superGameModule.superGameFailedTest();
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
