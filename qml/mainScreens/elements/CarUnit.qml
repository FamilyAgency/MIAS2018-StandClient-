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


    function moveCar()
    {
        var scaleFactor = consts.scaleFactor;
        var canvasY = 0;

        var curPoint = gameTaskManager.getCurPoint();

        car.x = curPoint.x * scaleFactor;
        car.y = canvasY + curPoint.y * scaleFactor;
        shadow.x = car.x;
        shadow.y = car.y;

        car.visible = true;
        car.scale = consts.artScaleFactor;
        shadow.scale = car.scale;

        var rotation = gameTaskManager.getForwardVectorRotation();
        var degrees = rotation * consts.toDegrees;
        car.rotation = degrees + consts.carAddAngle;
        shadow.rotation = car.rotation;
    }
}