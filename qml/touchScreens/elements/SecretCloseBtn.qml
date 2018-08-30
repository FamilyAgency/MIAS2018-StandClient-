import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item
{
    id: backbtn;
    anchors.fill:  parent;
    opacity: 0.0;

    property int maxClicks: 10;
    property int mills: 3000;
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
        anchors.horizontalCenter: parent.horizontalCenter;
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
                Qt.quit();
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
