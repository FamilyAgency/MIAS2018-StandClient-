import QtQuick 2.0

import "elements"
import "popups"
import "../tools"

Item
{
    id: gameView;
    anchors.fill: parent;

    Consts
    {
        id:consts;
    }

    Image
    {
        id:map
        anchors.fill: parent;
        smooth:true;
    }

    Road
    {
        id:road;
    }

    CarUnit
    {
        id:car;
    }

    Popup
    {
        id: pretaskPopup;
    }

    Component.onCompleted:
    {
        map.source = standData.getStandMap();
    }    


    Connections
    {
        target: rouletteModule;

        onShowSmallCar:
        {
            console.log("show small car !!!!!!!!!!!!");
            car.visible = true;
        }

        onUpdateCanvas:
        {
            car.moveCar(rouletteModule.getCurPoint(), rouletteModule.getForwardVectorRotation());
        }
    }

    Connections
    {
        target: gameTaskManager;

        onUpdateCanvas:
        {
            road.draw();
            car.moveCar(gameTaskManager.getCurPoint(), gameTaskManager.getForwardVectorRotation());
        }

        //        onPreTaskStartEvent:
        //        {
        //            consts.animateGuideColor();
        //        }
    }

    function gameStop()
    {
        console.log("=================== game stop ===================")
        car.visible = false;
        pretaskPopup.visible = false;
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        car.visible = true;
        pretaskPopup.visible = true;
    }
}
