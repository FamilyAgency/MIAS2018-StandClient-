import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item
{
    Text
    {
        text: "===================TESTS===================";
        font.family: "Helvetica";
        font.pixelSize: 18;
        color: "#990000";
    }

    ServerRemoteTest
    {
        y: 50;
    }

    RFIDTest
    {
        y: 500;
        visible:false;
    }

    Button
    {
        text: "Make Me Crash";
        visible:true;
        y: 800;
        onClicked: appController.testCrash();
    }
}
