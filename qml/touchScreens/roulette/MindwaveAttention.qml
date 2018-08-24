import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import "../../tools"

Item
{
    id:indicator;
    anchors.fill: parent;

    property double nextAttentionValue: 0.0;

    property string lineCap: "square";
    property string lineJoin: "round";

    property string colorBg: "#36565b";
    property string colorOuter: "#87d7e3";
    property string colorInner: "#f50a5c";

    property real percentInner: 0.0;
    property real percentOuter: 0.0;

    property real percentInnerThreshold: 0.4;
    property real percentOuterThreshold: 0.3;

    property int canvasWidth: 1080;
    property int canvasHeight: 1920;
    property int canvasHalfWidth: canvasWidth * 0.5;
    property int canvasHalfHeight: canvasHeight * 0.5;

    property int innerRadius: 736 * 0.5;
    property int outerRadius: 885 * 0.5;

    property int innerLineWidth: 26;
    property int outerLineWidth: 15;

    property bool starting: false;

    property real attentionThreshold: 0.6;

    property bool notifyOnce: false;

    signal mindwaveReady;

    onPercentInnerChanged:
    {
        if(starting && percentInner > attentionThreshold)
        {
            if(!notifyOnce)
            {
                notifyOnce = true;
                indicator.mindwaveReady();
            }
        }
    }

    Tools
    {
        id: tools;
    }

    Connections
    {
        target: mind;

        onAttentionChanged:
        {
            if(!starting)
            {
                return;
            }

            nextAttentionValue = mind.attention / 100.0;

            var animTo = tools.mapRangeClamp(nextAttentionValue, percentInnerThreshold, 1.0,  0.0, 1.0);
            maxAttentionAnim.to = animTo;
            maxAttentionAnim.duration = Math.abs(animTo - percentInner) * 2000;
            maxAttentionAnim.start();

            animTo = tools.mapRangeClamp(nextAttentionValue, 0.0, percentOuterThreshold,  0.0, 1.0);
            minAttentionAnim.to = animTo;
            maxAttentionAnim.duration = Math.abs(animTo - percentInner) * 2000;
            minAttentionAnim.start();
        }
    }

    Canvas
    {
        id: canvasCirc;
        width: canvasWidth;
        height: canvasHeight;
        antialiasing: true;
        smooth: true;

        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvasWidth, canvasHalfHeight);
            drawCircle(ctx, innerRadius, innerLineWidth, colorInner, percentInner);
            drawCircle(ctx, outerRadius, outerLineWidth, colorOuter, percentOuter);
        }

        PropertyAnimation
        {
            id: minAttentionAnim;
            target: indicator;
            property: "percentOuter";
            to: 100;
            duration: 50
            easing.type: "InOutCubic";
        }

        PropertyAnimation
        {
            id: maxAttentionAnim;
            target: indicator;
            property: "percentInner";
            to: 100;
            duration: 50;
            easing.type: "InOutCubic";
        }
    }

    Timer
    {
        id: cavasUpdater;
        running: false;
        interval: 100;
        repeat: true
        onTriggered:
        {
            canvasCirc.requestPaint();
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 1000;
        running: false;
        easing.type: "InOutCubic";

        onStopped:
        {
            if(opacity == 0)
            {
                visible = false;
            }
        }
    }

    function setLocation(x, y)
    {
       canvasCirc.x = x;
       canvasCirc.y = y;
    }

    function show()
    {
        cavasUpdater.running = true;
        starting = true;
        visible = true;

        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
    }

    function hide()
    {
        cavasUpdater.running = false;

        starting = false;
        notifyOnce = false;

        maxAttentionAnim.to = 0;
        maxAttentionAnim.duration = 500;
        maxAttentionAnim.start();

        minAttentionAnim.to = 0;
        minAttentionAnim.duration = 500;
        minAttentionAnim.start();

        opacityAnim.stop();
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.start();

        console.log("hide-----------------------")
    }

    function drawCircle(ctx, radius, lineWidth, color, percent)
    {
        ctx.lineCap = lineCap;
        ctx.lineJoin = lineJoin;
        ctx.lineWidth = lineWidth;
        ctx.strokeStyle = colorBg;

        ctx.beginPath();
        ctx.arc(canvasHalfWidth, canvasHalfHeight, radius, 0, 2 * Math.PI);
        ctx.stroke();
        ctx.closePath();

        ctx.strokeStyle = color;
        ctx.beginPath();
        ctx.arc(canvasHalfWidth, canvasHalfHeight, radius, 0, 2 * Math.PI * percent);
        ctx.stroke();
        ctx.closePath();
    }
}

