import QtQuick 2.0

import ".."
Item
{
    Consts
    {
        id:consts;
    }

    Connections
    {
        target:gameModule;

        onAllTaskComleteEvent:
        {
            visible = true;
        }
    }

    Connections
    {
        target:gameTaskManager;

        onPreTaskStartEvent:
        {
            var finishBulletSize = consts.finishBulletSize;
            visible = true;
            var endPoint = gameTaskManager.getEndPoint();
            x = endPoint.x * consts.scaleFactor - bullet.width * 0.5;
            y = consts.canvasY + endPoint.y * consts.scaleFactor - bullet.height - 20;
        }
    }

    //    Canvas
    //    {
    //        id: canVasBullet;
    //        width: 50;
    //        height: 50;
    //        onPaint:
    //        {
    //            var finishBulletSize = consts.finishBulletSize;

    //            var ctx = getContext("2d");
    //            ctx.fillStyle = consts.finishBulletColor;
    //            ctx.ellipse(0, 0, finishBulletSize, finishBulletSize);
    //            ctx.fill();
    //        }
    //    }

    Image
    {
        id:bullet
        // visible: false;
        smooth:true;
        antialiasing: true
        //  y: consts.canvasY;
        width: 137 * consts.artScaleFactor
        height: 259 * consts.artScaleFactor
        source: "qrc:/resources/finish.png"
        // transform: Translate {  x: -bullet.width * 0.5; y: -bullet.height}
    }
}
