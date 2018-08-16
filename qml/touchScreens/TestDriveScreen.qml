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
