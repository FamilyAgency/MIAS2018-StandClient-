import QtQuick 2.0

Item
{
    anchors.fill: parent;

    Image
    {
        id: shadow;
        source: consts.carShadowUrl;
        smooth:true;
        antialiasing: true;
        transform: Translate { x: -shadow.width * 0.5; y: -shadow.height * 0.5 }
    }

    Image
    {
        id:car
        width: consts.carWidth;
        height: consts.carHeight;
        source: consts.carUrl;
        smooth:true;
        antialiasing :true;
        transform: Translate { x: -car.width* 0.5; y: -car.height * 0.5}
    }

    CircularProgress
    {
        id: circProgress;
    }


    function moveCar(currentPoint, forwardVector)
    {
       var canvasY = 0;

        var curPoint = currentPoint;

        car.x = curPoint.x;
        car.y = canvasY + curPoint.y;
        shadow.x = car.x;
        shadow.y = car.y;

        car.visible = true;
        car.scale = consts.artScaleFactor;
        shadow.scale = car.scale;

        var rotation = forwardVector;
        var degrees = rotation * consts.toDegrees;
        car.rotation = degrees + consts.carAddAngle;
        shadow.rotation = car.rotation;

        circProgress.setCarPosition(currentPoint);
        circProgress.update();
    }

    function hideIndicator()
    {
        circProgress.visible = false;
    }

    function showIndicator()
    {
        circProgress.visible = true;
    }

    function setMindwaveLimitPercent(percent)
    {      
        circProgress.setMindwaveLimitPercent(percent);
    }

    function moveFromCanvas()
    {
        car.x = 0;
        car.y = 3000;
        shadow.x = car.x;
        shadow.y = car.y;

        circProgress.setCarPosition({x: 0, y: 3000});
        circProgress.update();
    }
}
