import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "elements"
import "supergame"
import "../tools"
import "testdrive"

Item
{
    id: testDrive;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "ТЕСТ ДРАЙВ";

    signal animComplete();
    signal animStart();

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }

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

    ChooseTestDrive
    {
        id: chooseTestDrive;
    }

    FinalTitle
    {
        id: finalTitle;
    }

    Connections
    {
        target: testDriveModule;

        onTestDriveRequestSuccess:
        {
            finalTitle.show();
        }
    }

    function start()
    {
        visible = true;
        testDrive.animComplete();
        chooseTestDrive.start();
        finalTitle.hide();
    }

    function stop()
    {
        visible = false;
    }
}
