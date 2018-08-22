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


    Image
    {
        id: flag;
        visible: false;
        property int currentImage: 1
        x: 0
        y: 0
        source: configController.getFileInAppDir("content/misc/flag/" + currentImage + ".png");
        NumberAnimation on currentImage
        {
            from: 0;
            to: 71;
            duration: 71 * 1000. / consts.animFPS;
            running: true;
            loops: Animation.Infinite;
        }
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

    CircularProgress
    {
        id: mindIndicator;
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
        mapover.source = standData.getStandMapOver();
    }

    Connections
    {
        target: rouletteModule;

        onShowSmallCar:
        {
            console.log("show small car !!!!!!!!!!!!");
            mindIndicator.hideIndicator();
            car.visible = true;
        }

        onUpdateCanvas:
        {
            car.moveCar(rouletteModule.getCurPoint(), rouletteModule.getForwardVectorRotation());
            mindIndicator.moveCar(rouletteModule.getCurPoint(), rouletteModule.getForwardVectorRotation());
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
            // road.circles = gameTaskManager.getTargetPoints();
            road.isSuperGame = false;
            road.hideSuperTrack();
            road.visible = true;
            road.draw();
            car.moveCar(gameTaskManager.getCurPoint(), gameTaskManager.getForwardVectorRotation());
            mindIndicator.moveCar(gameTaskManager.getCurPoint(), gameTaskManager.getForwardVectorRotation());
        }

        onPreTaskStartEvent:
        {
            mindIndicator.showIndicator();
            mindIndicator.setMindwaveLimitPercent(gameTaskManager.getMindwaveLimit());
        }

        onGameStarted:
        {
            road.init();
            road.visible = true;
            //  road.circles = gameTaskManager.getTargetPoints();
            var circles = gameTaskManager.getTargetPoints();
            var lastPoint = circles[circles.length - 1];
            road.circles = circles;
            setFlagPosition(lastPoint.x, lastPoint.y);
            showFlag();
            road.show();
        }

        onTaskComleteEvent:
        {
            console.log("========task complete=========");
            road.taskComplete();
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
            mindIndicator.moveCar(superGameModule.getCurPoint(), superGameModule.getForwardVectorRotation());
        }

        onCountDownComplete:
        {
            road.visible = true;

            var circles = superGameModule.getGameUncompletedPath();
            var lastPoint = circles[circles.length - 1];
            setFlagPosition(lastPoint.x, lastPoint.y);
            showFlag();

            var startPoint = superGameModule.getStartPoint();
            road.setSuperTrackPosition(startPoint);
            road.setSuperTrackRotation(superGameModule.getForwardVectorRotation());

            road.calcSuperTrackLength(startPoint, lastPoint);

            road.showSuperTrack();

            road.show();
            mindIndicator.showIndicator();
            mindIndicator.setMindwaveLimitPercent(superGameModule.getMindwaveLimit());
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
        hideFlag();
        car.moveFromCanvas();
        mindIndicator.moveFromCanvas();
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        car.visible = true;
        road.visible = true;
        pretaskPopup.visible = true;
    }
    function setFlagPosition(x, y)
    {
        flag.x = x - 10;
        flag.y = y - 66;
    }

    function showFlag()
    {
        flag.visible = true;
    }

    function hideFlag()
    {
        flag.visible = false;
    }

}
