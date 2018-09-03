import QtQuick 2.0

import "../../tools"
import "../../touchScreens/roulette"

Item
{
    property int canvasSize: 240;

    visible: false;

    Consts
    {
        id: consts;
    }

    MindwaveAttention
    {
        id: mindwaveAttention;
        visible: true;

        arcPercent: 0.7;
        innerRadius: 65;
        outerRadius: 75;
        innerLineWidth: 7;
        outerLineWidth: 6;

        canvasWidth: canvasSize;
        canvasHeight: canvasSize;
        canvasHalfWidth: canvasSize * 0.5;
        canvasHalfHeight: canvasSize * 0.5;
    }

    function hideIndicator()
    {
        visible = false;
        mindwaveAttention.hide();
    }

    function showIndicator()
    {
        visible = true;
        mindwaveAttention.show();
    }

    function moveCar(currentPoint, forwardVector, forwardVectorRot)
    {
        var rotation = forwardVectorRot;
        var degrees = rotation * consts.toDegrees;
        mindwaveAttention.setRotation(degrees + consts.carAddAngle - 40);

        currentPoint.x -= forwardVector.x * 60;
        currentPoint.y -= forwardVector.y * 60;
        setCarPosition(currentPoint);
        update();
    }

    function moveFromCanvas()
    {
        setCarPosition({x: 0, y: 3000});
        hideIndicator();
    }    

    function setCarPosition(currentPoint)
    {
        var x = currentPoint.x - canvasSize * 0.5;
        var y = currentPoint.y - canvasSize * 0.5;
        mindwaveAttention.setLocation(x, y);
    }

    function setMindwaveLimitPercent(percent)
    {
        var _percent = percent / 100.0;
        mindwaveAttention.attentionThreshold = _percent;
    }
}
