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
        visible: false;
    }

    CarUnit
    {
        id:car;
        visible: false;
    }

    Popup
    {
        id: pretaskPopup;
        visible: false;
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
            road.isRunning = gameTaskManager.isRunning()
            road.isPreTaskState = gameTaskManager.isPreTaskState()
            road.completedPath = gameTaskManager.getCompletedPath()
            road.currentPoint = gameTaskManager.getCurPoint();
            road.startPoint = gameTaskManager.getStartPoint();
            road.fullGamePath =  gameTaskManager.getFullGamePath();
            road.circles = gameTaskManager.getTargetPoints();
            road.isDrawCircles = true;
            road.visible = true;
            road.draw();
            car.moveCar(gameTaskManager.getCurPoint(), gameTaskManager.getForwardVectorRotation());
        }

        onPreTaskStartEvent:
        {
           car.setMindwaveLimitPercent(gameTaskManager.getMindwaveLimit());
        }
    }

    Connections
    {
        target: superGameModule;
        onUpdateCanvas:
        {
            car.visible = true;

            road.isRunning = superGameModule.isRunning()
            road.isPreTaskState = superGameModule.isPreTaskState()
            road.completedPath = superGameModule.getCompletedPath()
            road.currentPoint = superGameModule.getCurPoint();
            road.startPoint = superGameModule.getStartPoint();
            road.fullGamePath =  superGameModule.getFullGamePath();
            road.isDrawCircles = false;
            road.visible = true;
            road.draw();
            car.moveCar(superGameModule.getCurPoint(), superGameModule.getForwardVectorRotation());
        }

        onCountDownComplete:
        {
            car.setMindwaveLimitPercent(superGameModule.getMindwaveLimit());
        }
    }

    function gameStop()
    {
        console.log("=================== game stop ===================")
        car.visible = false;
        road.visible = false;
        pretaskPopup.visible = false;
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        car.visible = true;
        road.visible = true;
        pretaskPopup.visible = true;
    }
}
