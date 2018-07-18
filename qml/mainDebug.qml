import QtQuick 2.0
import QtQuick.Controls 2.2
import "tests/touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{
    visible: true;
    width: 1500;
    height: 900;
    x: 420;
    y: 100;
    title: qsTr("App");
    id: core;

    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;



    Item
    {
        focus: true;

        Keys.onPressed:
        {
            if (event.key === Qt.Key_Escape)
            {
                Qt.quit();
            }
        }
    }

    TouchWindowTest
    {
        id:touchWindow;
    }

    MainWindow
    {
        id:mainWindow;
    }

    ControlsWindow
    {
        id:controlsWindow;
    }
}
