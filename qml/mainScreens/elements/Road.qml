import QtQuick 2.2
import QtQuick.Controls.Styles 1.4
import "../../tools"

Item
{
    anchors.fill: parent;

    property real arrowSize: 26.0;
    property int lineWidth: 10;
    property string activeLineColor: "#f3095d";
    property string nonActiveLineColor: "#20346e";
    property string blueArrow: "qrc:/resources/superarrow.png";
    property string redArrow: "qrc:/resources/superarrow1.png";

    property var isRunning;
    property var isPreTaskState;
    property var completedPath;
    property var uncompletedPath;
    property var currentPoint;
    property var startPoint;
    property var circles;
    property bool isSuperGame: false;
    property int pointsCompleted: 0;
    property int animatedItemIndex: 0;
    property var startPoint1;
    property var startPoint2;
    property var superGameLastPoint;
    property int superGameLength: 0;

    Consts
    {
        id:consts;
    }

    AnimationPlayer
    {
        id: pulsAnim;
        currentImage: 2;
        endFrame: 46;
        startFrame: 2;
        Component.onCompleted:
        {
            pulsAnim.setSource("content/misc/puls/", ".png");
            pulsAnim.setFPS(30);
            pulsAnim.init();
        }
    }

    Canvas
    {
        id: canvas;

        property string greycircle: "qrc:/resources/Star_blue.png";
        property string redcircle: "qrc:/resources/Star_white.png";

        property string lineCap: "square";
        property string lineJoin: "round";

        anchors.fill: parent;
        antialiasing: true;
        smooth: true;

        Component.onCompleted:
        {
            loadImage(canvas.greycircle);
            loadImage(canvas.redcircle);
        }

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            if(isPreTaskState || isRunning)
            {
                if(isSuperGame)
                {
                    return;
                }

                drawGuidePaths(ctx);
                var list = completedPath;

                ctx.lineWidth = lineWidth;
                ctx.strokeStyle = nonActiveLineColor;
                ctx.lineCap = lineCap;
                ctx.lineJoin = lineJoin;

                ctx.beginPath();
                ctx.moveTo(startPoint1.x, startPoint1.y);
                ctx.lineTo(startPoint2.x, startPoint2.y);
                ctx.stroke();
                ctx.closePath();

                var curPoint = currentPoint;
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

    Item
    {
        id: superTrackHolder;
        rotation: 10;

        Row
        {
            id: superTrack;
            Repeater
            {
                id: repeater;
                model: 0;
                Image
                {
                    smooth:true;
                    antialiasing: true;
                    id: arrow;
                    source: redArrow;
                }
            }
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running: false;
        easing.type: "InOutCubic";
    }

    function setStartPath(point1, point2)
    {
        startPoint1 = point1;
        startPoint2 = point2;
    }

    function animateSuperTrack()
    {
        var size = repeater.model;

        if(size > 0)
        {
            for(var i = 0; i < size; i++)
            {
                repeater.itemAt(i).opacity = 1;
            }

            repeater.itemAt(animatedItemIndex).opacity = 0;
            animatedItemIndex = (animatedItemIndex + 1) % size;
        }
    }

    function calcSuperTrackLength(startPosition, endPosition)
    {
        var a = endPosition.x - startPosition.x;
        var b = endPosition.y - startPosition.y;

        var c = Math.sqrt( a*a + b*b );

        repeater.model = Math.floor(c / arrowSize);

        for(var i = 0; i <  repeater.model; i++)
        {
            repeater.itemAt(i).source = redArrow;
        }

        superGameLength = vecLength(startPosition, endPosition);
    }

    function updateSuperGamePercent()
    {
        var completedLength = vecLength(currentPoint, superGameLastPoint);
        var percent = 1 - completedLength/superGameLength;

        var countToShow = Math.floor(repeater.model * percent);
        for(var i = 0; i < countToShow; i++)
        {
            repeater.itemAt(i).source = blueArrow;
        }

        for(var j = countToShow; j < repeater.model; j++)
        {
            repeater.itemAt(j).source = redArrow;
        }
    }

    function setSuperTrackRotation(forwardVector)
    {
        var rotation = forwardVector;
        var degrees = rotation * consts.toDegrees;
        superTrackHolder.rotation = degrees;
    }

    function setSuperTrackPosition(position)
    {
        superTrackHolder.x = position.x;// - arrowSize * 0.5;
        superTrackHolder.y = position.y - arrowSize * 0.5;
    }

    function showSuperTrack()
    {
        pulsAnim.visible = false;
        pulsAnim.setRunning(false);
        superTrack.visible = true;
    }

    function hideSuperTrack()
    {
        superTrack.visible = false;
    }

    function show()
    {
        opacity = 0;
        pulsAnim.visible = true;
        pulsAnim.setRunning(true);

        opacityAnim.start();
    }

    function draw()
    {
        canvas.requestPaint();
    }

    function init()
    {
        pointsCompleted = 0;
    }

    function taskComplete()
    {
        pointsCompleted++;
    }


    function drawSuperGameGuidePaths(ctx)
    {
        var list = uncompletedPath;

        ctx.beginPath();
        ctx.moveTo(list[0].x, list[0].y);
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = lineWidth;

        for(var i = 1; i < list.length; i++)
        {
            ctx.lineTo(list[i].x, list[i].y);
        }

        ctx.stroke();
        ctx.closePath();
    }

    function drawGuidePaths(ctx)
    {
        var list = uncompletedPath;

        ctx.beginPath();
        ctx.moveTo(currentPoint.x, currentPoint.y);
        ctx.strokeStyle =  activeLineColor;
        ctx.lineWidth = lineWidth;

        for(var i = 0; i < list.length; i++)
        {
            ctx.lineTo(list[i].x, list[i].y);
        }

        ctx.stroke();
        ctx.closePath();
    }

    function drawCircles(ctx)
    {
        var ellipseSize = 20;

        for(var i = 0; i < pointsCompleted; i++)
        {
            ctx.drawImage(canvas.greycircle, circles[i].x - 25, circles[i].y - 25);
        }

        for(var k = pointsCompleted; k < circles.length - 1; k++)
        {
            ctx.drawImage(canvas.redcircle, circles[k].x - 25, circles[k].y - 25);
        }

        pulsAnim.setLocation(circles[pointsCompleted].x - 82, circles[pointsCompleted].y - 82);
    }

    function drawFlag(ctx)
    {
        var ellipseSize = 35;

        var k = circles.length - 1;
        ctx.beginPath();
        ctx.fillStyle =  "#ffffff";
        ctx.strokeStyle =  "#ff0000";
        ctx.lineWidth = 21;
        ctx.ellipse(circles[k].x - ellipseSize * 0.5, circles[k].y - ellipseSize * 0.5, ellipseSize, ellipseSize);
        ctx.stroke();
        ctx.fill();
        ctx.closePath();
    }

    function vecLength(point1, point2)
    {
        var x = point2.x - point1.x;
        var y = point2.y - point1.y;
        return Math.sqrt( x*x + y*y );
    }
}
