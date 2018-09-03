import QtQuick 2.0

import "elements"
import "popups"

Item
{
    id: gameView;
    anchors.fill: parent;

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

    Flag
    {
        id: flag;
        visible: false;
    }

    CarUnit
    {
        id:car;
        visible: false;
    }

    Image
    {
        id:mapover
        anchors.fill: parent;
        smooth:true;
    }

    MapAnimator
    {
        id: mapAnimator;
    }

    CircularProgress
    {
        id: mindIndicator;
    }

    Popup
    {
        id: pretaskPopup;
        visible: false;
    }

    Component.onCompleted:
    {
        map.source = standData.getStandMap();
        mapover.source = standData.getStandMapOver();
    }

    Connections
    {
        target: gameModule;

        onAllStagesComleteEvent:
        {
            flag.hide();
            car.moveFromCanvas();
            mindIndicator.moveFromCanvas();
        }
    }

    Connections
    {
        target: rouletteModule;

        onShowSmallCar:
        {
            mindIndicator.hideIndicator();
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
            updateGameTask(gameTaskManager);
            road.draw();
        }

        onPreTaskStartEvent:
        {
            mindIndicator.showIndicator();
            mindIndicator.setMindwaveLimitPercent(gameTaskManager.getMindwaveLimit());
        }

        onGameStarted:
        {
            var circles = gameTaskManager.getTargetPoints();
            var lastPoint = circles[circles.length - 1];

            road.isSuperGame = false;
            road.hideSuperTrack();
            road.visible = true;
            road.setStartPath(gameTaskManager.getStartPoint1(), gameTaskManager.getStartPoint2());
            road.init();
            road.show();
            road.circles = circles;

            flag.setFlagPosition(lastPoint.x, lastPoint.y);
            flag.show();
        }

        onTaskComleteEvent:
        {
            road.taskComplete();
        }
    }

    Connections
    {
        target: superGameModule;
        onUpdateCanvas:
        {
           updateGameTask(superGameModule);
           road.updateSuperGamePercent();
        }

        onSuperGameStarted:
        {
            var circles = superGameModule.getGameUncompletedPath();
            var lastPoint = circles[circles.length - 1];
            flag.setFlagPosition(lastPoint.x, lastPoint.y);
            flag.show();

            var startPoint = superGameModule.getStartPoint();
            road.setSuperTrackPosition(startPoint);
            road.setSuperTrackRotation(superGameModule.getForwardVectorRotation());
            road.calcSuperTrackLength(startPoint, lastPoint);
            road.superGameLastPoint = lastPoint;
            road.visible = true;
            road.isSuperGame = true;
            road.show();
            road.showSuperTrack();

            mindIndicator.showIndicator();
            mindIndicator.setMindwaveLimitPercent(superGameModule.getMindwaveLimit());
            mindIndicator.moveCar(superGameModule.getCurPoint(), superGameModule.getForwardVector(), superGameModule.getForwardVectorRotation());

            car.visible = true;
            car.moveCar(superGameModule.getCurPoint(), superGameModule.getForwardVectorRotation());
        }

        onSuperGameFailed:
        {
            gameStop();
        }

        onSuperGameSuccess:
        {
            gameStop();
        }
    }

    function updateGameTask(provicer)
    {
        road.isRunning = provicer.isRunning()
        road.isPreTaskState = provicer.isPreTaskState()
        road.completedPath = provicer.getCompletedPath()
        road.currentPoint = provicer.getCurPoint();
        road.startPoint = provicer.getStartPoint();
        road.uncompletedPath =  provicer.getGameUncompletedPath();

        car.moveCar(provicer.getCurPoint(), provicer.getForwardVectorRotation());
        mindIndicator.moveCar(provicer.getCurPoint(), provicer.getForwardVector(), provicer.getForwardVectorRotation());
    }

    function gameStop()
    {
        console.log("=================== game stop ===================")

        car.visible = false;
        car.moveFromCanvas();

        road.visible = false;
        pretaskPopup.visible = false;
        flag.hide();

        mindIndicator.moveFromCanvas();
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        car.visible = true;
        road.visible = true;
        pretaskPopup.visible = true;
    }
}
