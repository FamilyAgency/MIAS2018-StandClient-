import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item
{
    id: backbtn;
    anchors.fill:  parent;
    opacity: 0.1;

    property int maxClicks: 1;
    property int mills: 2000;
    property int currentClick: 0;

    Button
    {
        id: backBtn;
        text: "";
        visible: true;
        width: 100;
        height: 100;
        anchors.top: parent.top;
        anchors.topMargin: 0;
        anchors.left: parent.left;
        anchors.rightMargin: 0;
        onClicked:
        {
            if(currentClick++ == 0)
            {
                timer.start();
            }

            if(currentClick >= maxClicks)
            {
                currentClick = 0;
                timer.stop();
                appController.backToIntro();
            }
        }
    }

    Timer
    {
        id: timer;
        interval: 2000;

        onTriggered:
        {
            currentClick = 0;
        }
    }
}
