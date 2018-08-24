import QtQuick 2.0

import "../../tools"

Item
{
    property double nextAttentionValue: 0.0;
    visible:false;

    Consts
    {
        id:consts;
    }

    Connections
    {
        target: mind;
        onAttentionChanged:
        {
            nextAttentionValue = mind.attention / 100.0;
            //canvasCirc.percentAttention = nextAttentionValue;
            attentionAnim.to = nextAttentionValue;
            attentionAnim.duration = 100;
            attentionAnim.start();
        }
    }

    function hideIndicator()
    {
        visible = false;
    }

    function showIndicator()
    {
        visible = true;
    }

    function moveCar(currentPoint, forwardVector)
    {
        setCarPosition(currentPoint);
        update();
    }

    function moveFromCanvas()
    {
        setCarPosition({x: 0, y: 3000});
        update();
    }

    function update()
    {
        canvasCirc.requestPaint();
    }

    function setMindWaveLimit(limit)
    {
         canvasCirc.percentLimit =limit;// gameTaskManager.getMindwaveLimit();
    }

    function setCarPosition(currentPoint)
    {
        var startPoint = currentPoint;
        x = startPoint.x * consts.scaleFactor - canvasCirc.width * 0.5;
        y = consts.canvasY + startPoint.y * consts.scaleFactor - canvasCirc.height * 0.5;
    }

    function setMindwaveLimitPercent(percent)
    {
        canvasCirc.percentLimit = percent;
    }

    Canvas
    {
        id: canvasCirc;
        width: 250;
        height: 250;
        property int centerWidth: 250 * 0.5
        property int centerHeight: 250 * 0.5
        property int radius: 80;

        property real percentLimit: 0.0;
        property real percentAttention: 0.0;

        onPaint:
        {
            var lineWidth = 10;

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, 250, 250);

            ctx.lineCap = "square";
            ctx.lineJoin = "round";

            ctx.lineWidth = lineWidth;

            ctx.strokeStyle = "#36565b";;
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2 * Math.PI);
            ctx.stroke();
            ctx.closePath();

//            ctx.strokeStyle = colorLimit;
//            ctx.beginPath();
//            ctx.arc(canvasCirc.centerWidth,
//                    canvasCirc.centerHeight,
//                    canvasCirc.radius,
//                    0,
//                    2*Math.PI * canvasCirc.percentLimit);
//            ctx.stroke();
//            ctx.closePath();

            var col =  "#ffffff";
//            if(canvasCirc.percentAttention > canvasCirc.percentLimit )
//            {
//                col =  "#f50a5c";;
//            }
//            else
//            {
//                col = "#f50a5c";
//            }

            ctx.strokeStyle = "#f50a5c";
            ctx.beginPath();
            ctx.arc(canvasCirc.centerWidth,
                    canvasCirc.centerHeight,
                    canvasCirc.radius,
                    0,
                    2 * Math.PI * canvasCirc.percentAttention);
            ctx.stroke();
            ctx.closePath();
        }

        PropertyAnimation
        {
            id: attentionAnim;
            target: canvasCirc;
            property: "percentAttention";
            to: 100;
            duration: 50
        }
    }
}
