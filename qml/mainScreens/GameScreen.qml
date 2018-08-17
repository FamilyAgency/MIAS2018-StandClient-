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
        id: road;
        visible: false;
    }

    CarUnit
    {
        id:car;
        visible: false;
    }

    MapAnimator
    {
        id: mapAnimator;
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
            car.hideIndicator();
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
            road.uncompletedPath =  gameTaskManager.getGameUncompletedPath();
            road.circles = gameTaskManager.getTargetPoints();          
            road.isSuperGame = false;
            road.hideSuperTrack();
            road.visible = true;
            road.draw();
            car.moveCar(gameTaskManager.getCurPoint(), gameTaskManager.getForwardVectorRotation());
        }

        onPreTaskStartEvent:
        {
            car.showIndicator();
            car.setMindwaveLimitPercent(gameTaskManager.getMindwaveLimit());
        }

        onGameStarted:
        {
            road.visible = true;
            var circles = gameTaskManager.getTargetPoints();
            var lastPoint = circles[circles.length - 1];
            road.setFlagPosition(lastPoint.x, lastPoint.y);
            road.show();
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
            road.uncompletedPath =  superGameModule.getGameUncompletedPath();
            road.visible = true;
            road.isSuperGame = true;
            road.draw();
            car.moveCar(superGameModule.getCurPoint(), superGameModule.getForwardVectorRotation());
        }

        onCountDownComplete:
        {
            road.visible = true;
            var circles = superGameModule.getGameUncompletedPath();
            var lastPoint = circles[circles.length - 1];
            road.setFlagPosition(lastPoint.x, lastPoint.y);

            var startPoint = superGameModule.getStartPoint();
            road.setSuperTrackPosition(startPoint);
            road.setSuperTrackRotation(superGameModule.getForwardVectorRotation());

            road.calcSuperTrackLength(startPoint, lastPoint);

            road.showSuperTrack();

            road.show();
            car.showIndicator();
            car.setMindwaveLimitPercent(superGameModule.getMindwaveLimit());
        }

        onSuperGameFailed:
        {

        }
    }

    function gameStop()
    {
        console.log("=================== game stop ===================")

        car.visible = false;
        road.visible = false;
        pretaskPopup.visible = false;
        car.moveFromCanvas();
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        car.visible = true;
        road.visible = true;
        pretaskPopup.visible = true;
    }
}
