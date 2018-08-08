import QtQuick 2.0
import QtQuick.Controls 2.2
import "tests/touchScreens"
import "touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{   
    title: "Touch Window";
    x: standData.mainConfig.touchScreen.x;
    y: standData.mainConfig.touchScreen.y;
    width: standData.mainConfig.touchScreen.width;
    height: standData.mainConfig.touchScreen.height;
    visible: true;
    flags: standData.mainConfig.touchScreenIsSplash ? Qt.SplashScreen : Qt.Window;
    color: "#101010";

    id: core;

    TouchWindow
    {
        id:touchWindow;

//        TouchWindowTest
//        {

//        }
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
