import QtQuick 2.0
import QtQuick.Controls 2.2
import "touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{    
    title: qsTr("App");
    x: 0;
    y: 0;
    width: 100;
    height: 100;
    visible: true;

    id: core;

    TouchWindow
    {
        id:touchWindow;
    }

    MainWindow
    {
        id:mainWindow
    }
}
