import QtQuick 2.0

import "../../tools"

Item
{
    anchors.fill: parent;

    Consts
    {
        id: consts;
    }

    Image
    {
        id: shadow;
        source: "qrc:/resources/Glow_Car.png";
        smooth: true;
        antialiasing: true;
        transform: Translate { x: -shadow.width * 0.5; y: -shadow.height * 0.5 }
    }

    Image
    {
        id: car;
        width: 64;
        height: 124;
        source: "qrc:/resources/car2.png";
        smooth: true;
        antialiasing: true;
        transform: Translate { x: -car.width * 0.5; y: -car.height * 0.5; }
    }   

    function moveCar(currentPoint, forwardVector)
    {
        var curPoint = currentPoint;

        car.x = curPoint.x;
        car.y = curPoint.y;
        shadow.x = car.x;
        shadow.y = car.y;

        car.visible = true;       
        shadow.scale = car.scale;

        var rotation = forwardVector;
        var degrees = rotation * consts.toDegrees;
        car.rotation = degrees + consts.carAddAngle;
        shadow.rotation = car.rotation;      
    }

    function moveFromCanvas()
    {
        car.x = 0;
        car.y = 3000;
        shadow.x = car.x;
        shadow.y = car.y;
    }
}
