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

    OpacityAnimator on opacity
    {
        id:opacityAnim;
        from: 0;
        to: 1;
        running:false;
        duration: 700;
        easing.type: "InOutQuad";
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
        opacity = 0;
        opacityAnim.start();
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
