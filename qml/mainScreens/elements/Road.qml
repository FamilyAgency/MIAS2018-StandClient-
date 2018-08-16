import QtQuick 2.0

Item
{
    anchors.fill: parent;

    Canvas
    {
        id: canvas;
        anchors.fill: parent;
        antialiasing: true;

        onPaint:
        {
            var scaleFactor = consts.scaleFactor;
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            if(gameTaskManager.isPreTaskState() || gameTaskManager.isRunning())
            {
                drawGuidePaths(ctx);
                // drawCircles(ctx);
                // moveCar();


                // if(gameTaskManager.isRunning())
                //  {
                //    drawGuidePaths(ctx);
                var list = gameTaskManager.getCompletedPath();

                ctx.lineWidth = consts.lineWidth;
                ctx.strokeStyle =  "#ffff00";

                ctx.lineCap = consts.lineCap;
                ctx.lineJoin = consts.lineJoin;

                var curPoint = gameTaskManager.getCurPoint();
                if(list.length > 1)
                {
                    ctx.beginPath();
                    ctx.moveTo(list[0].x, list[0].y);
                    for(var i = 1; i < list.length; i++)
                    {
                        ctx.lineTo(list[i].x, list[i].y);
                    }

                    ctx.lineTo(curPoint.x, curPoint.y);
                    ctx.stroke();
                    ctx.closePath();
                }
                else
                {
                    var startPoint = gameTaskManager.getStartPoint();
                    ctx.beginPath();
                    ctx.moveTo(startPoint.x, startPoint.y );
                    ctx.lineTo(curPoint.x, curPoint.y);
                    ctx.stroke();
                    ctx.closePath();

                }

                drawCircles(ctx);
            }
        }
    }

    function draw()
    {
         canvas.requestPaint();
    }

    function drawGuidePaths(ctx)
    {
        var scaleFactor = consts.scaleFactor;
        var list = gameTaskManager.getFullGamePath();

        ctx.beginPath();
        ctx.moveTo(list[0].x * scaleFactor, list[0].y * scaleFactor);
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = consts.lineWidth;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x * scaleFactor, list[i].y * scaleFactor);
        }
        ctx.stroke();
        ctx.closePath();
    }

    function drawCircles(ctx)
    {
        var circles = gameTaskManager.getTargetPoints();
        for(var k = 0; k < circles.length; k++)
        {
            ctx.beginPath();
            // console.log(circles[k].x, circles[k].y)
            ctx.fillStyle =  "#ffffff";
            ctx.strokeStyle =  "#ff0000";
            ctx.lineWidth = 18;
            var ellipseSize = 20;
            ctx.ellipse(circles[k].x - ellipseSize * 0.5, circles[k].y - ellipseSize * 0.5, ellipseSize, ellipseSize);
            ctx.stroke();
            ctx.fill();
            ctx.closePath();
        }
    }
}
