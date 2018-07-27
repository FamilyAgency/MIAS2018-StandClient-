import QtQuick 2.0
import QtQuick.Controls 2.2
import "tests/touchScreens"
import "touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{
    visible: true;
    width: 1500;
    height: 700;
    x: 420;
    y: 100;
    title: qsTr("App");
    id: core;

//    TouchWindow
//    {
//        id:touchWindow;

//        TouchWindowTest
//        {

//        }
//    }

//    MainWindow
//    {
//        id:mainWindow;
//    }

    ControlsWindow
    {
        id:controlsWindow;
    }
}
