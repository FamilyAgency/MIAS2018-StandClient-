import QtQuick 2.0
import QtQuick.Controls 2.2
import "tests/touchScreens"
import "touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{   
    title: qsTr("App");
    x: 420;
    y: 20;
    width: 1500;
    height: 900;
    visible: true;

    id: core;

    TouchWindow
    {
        id:touchWindow;

        TouchWindowTest
        {

        }
    }

    MainWindow
    {
        id:mainWindow;
       // visible:false;
    }

    ControlsWindow
    {
        id:controlsWindow;
    }
}
