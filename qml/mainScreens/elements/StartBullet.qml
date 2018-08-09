import QtQuick 2.0
import "../../tools"

Item
{
    Consts
    {
        id:consts;
    }

    Connections
    {
        target:gameModule;

        onAllStagesComleteEvent:
        {
            visible = true;
        }
    }

    Connections
    {
        target:gameTaskManager;

        onPreTaskStartEvent:
        {
            visible = true;
            var startPoint = gameTaskManager.getStartPoint();
            x = startPoint.x * consts.scaleFactor - consts.bulletSize * 0.5;
            y = consts.canvasY + startPoint.y * consts.scaleFactor - consts.bulletSize * 0.5;
        }
    }

    Canvas
    {
        id: canVasBullet;
        width: 50;
        height: 50;

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.fillStyle = consts.startBulletColor;
            ctx.ellipse(0, 0, consts.bulletSize, consts.bulletSize);
            ctx.fill();
        }
    }

//    Image
//    {
//        id:bullet
//       // visible: false;
//        smooth:true;
//        antialiasing: true
//      //  y: consts.canvasY;
//        width: 136 * consts.artScaleFactor
//        height: 259 * consts.artScaleFactor
//        source: "qrc:/resources/start.png"
//        transform: Translate { x: -bullet.width * 0.5; y: -bullet.height}
//    }
}
