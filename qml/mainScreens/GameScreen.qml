import QtQuick 2.0

import "elements"
import "popups"

Item {

    id:gameView

    property int canvasWidth: 1600;
    property int canvasHeight: 900;

    anchors.fill: parent;

    Consts
    {
        id:consts;
    }

    Connections
    {
        target:gameTaskManager;

        onUpdateCanvas:
        {
            canvas.requestPaint();
        }

        onPreTaskStartEvent:
        {
            consts.animateGuideColor();
        }
    }

    Component.onCompleted:
    {
        road.source = configController.getQMLFile("content/maps/map" + standData.mainConfig.appId + ".png");
    }

    Image
    {
        id:road      
        anchors.fill: parent;
        smooth:true;
    }

    Canvas
    {
        id: canvas;
        anchors.fill: parent;
        antialiasing: true;

        onPaint:
        {
            var scaleFactor = consts.scaleFactor;
            var ctx = getContext("2d");
            console.log(canvas.width, canvas.height);
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            if(gameTaskManager.isPreTaskState())
            {
                drawGuidePaths(ctx);
                moveCar();
            }

            if(gameTaskManager.isRunning())
            {
                drawGuidePaths(ctx);
                var list = gameTaskManager.getCompletedPath();

                ctx.lineWidth = consts.lineWidth;
                ctx.strokeStyle = consts.redColor;
                ctx.lineCap = consts.lineCap;
                ctx.lineJoin = consts.lineJoin;

                if(list.length > 1)
                {
                    ctx.beginPath();
                    ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
                    for(var i = 1; i < list.length; i++)
                    {
                        ctx.lineTo(list[i].x * scaleFactor, list[i].y * scaleFactor);
                    }
                }
                else
                {
                    ctx.beginPath();
                    var startPoint = gameTaskManager.getStartPoint();
                    ctx.moveTo(startPoint.x * scaleFactor, startPoint.y * scaleFactor);
                }

                var curPoint = gameTaskManager.getCurPoint();
                ctx.lineTo(curPoint.x * scaleFactor, curPoint.y * scaleFactor);
                ctx.stroke();
                ctx.closePath();

                moveCar();
            }
        }
    }

    FinishBullet
    {
        id: finishBullet;
        visible: false;
        y: consts.canvasY;
    }

    StartBullet
    {
        id: startBullet;
        visible: false;
        y: consts.canvasY;
    }

    Image
    {
        id: shadow;
        y: consts.canvasY;
        visible: false;
        source: consts.carShadowUrl;
        smooth:true;
        antialiasing :true;
        transform: Translate { x: -shadow.width * 0.5; y: -shadow.height * 0.5 }
    }

    Image
    {
        id:car
        visible: false;
        y: consts.canvasY;
        width: consts.carWidth;
        height: consts.carHeight;
        source: consts.carUrl;
        smooth:true;
        antialiasing :true;
        transform: Translate { x: -car.width* 0.5; y: -car.height * 0.5}
    }

    CircularProgress
    {
        id: circProgress
        visible: false;
        y: consts.canvasY;
    }

    PreTaskPopup
    {
        id: pretaskPopup
        x: canvas.width - 300 - 10;
        y: 100 + 10;
    }

    function drawGuidePaths(ctx)
    {
        var scaleFactor = consts.scaleFactor;
        var list = gameTaskManager.getFullPath();

        ctx.beginPath();
        ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
        ctx.strokeStyle =  consts.guideColor;
        ctx.lineWidth = consts.lineWidth;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x * scaleFactor, list[i].y * scaleFactor);
        }
        ctx.stroke();
        ctx.closePath();
    }

    function moveCar()
    {
        var scaleFactor = consts.scaleFactor;
        var canvasY = consts.canvasY;

        var curPoint = gameTaskManager.getCurPoint();

        car.x = curPoint.x * scaleFactor;
        car.y = canvasY + curPoint.y * scaleFactor;
        car.visible = true;
        car.scale = consts.artScaleFactor;

        var rotation = gameTaskManager.getForwardVectorRotation();
        var degrees = rotation * consts.toDegrees;
        car.rotation = degrees + consts.carAddAngle;

        shadow.x = car.x;
        shadow.y = car.y;
        shadow.scale = car.scale;
        shadow.visible = true;
        shadow.rotation = car.rotation;
    }

    function gameStop()
    {
        console.log("=================== game stop ===================")
        car.visible = false;
        shadow.visible = false;
        finishBullet.visible = false;
        circProgress.visible = false;
        startBullet.visible = false;
        pretaskPopup.visible = false;
    }

    function gameStart()
    {
        console.log("=================== game start ===================")
        finishBullet.visible = true;
        circProgress.visible = true;
        startBullet.visible = true;
        pretaskPopup.visible = true;
    }
}
