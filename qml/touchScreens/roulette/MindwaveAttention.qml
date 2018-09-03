import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import "../../tools"

Item
{
    id: indicator;
    anchors.fill: parent;

    property string lineCap: "square";
    property string lineJoin: "round";

    property string colorBg: "#36565b";
    property string colorOuter: "#87d7e3";
    property string colorInner: "#f50a5c";

    property real percentInner: 0.0;
    property real percentOuter: 0.0;

    property real percentInnerThreshold: 0.4;
    property real percentOuterThreshold: 0.2;

    property int canvasWidth: 1080;
    property int canvasHeight: 1920;
    property int canvasHalfWidth: canvasWidth * 0.5;
    property int canvasHalfHeight: canvasHeight * 0.5;

    property int innerRadius: 836 * 0.5;
    property int outerRadius: 885 * 0.5;

    property int innerLineWidth: 26;
    property int outerLineWidth: 15;

    property bool starting: false;

    property real attentionThreshold: 0.9;

    property bool notifyOnce: false;

    property real arcPercent: 1.0;

    signal attentionGood();

    onPercentInnerChanged:
    {
        if(starting && percentInner >= attentionThreshold)
        {
            if(!notifyOnce)
            {
                notifyOnce = true;
                indicator.attentionGood();
            }
        }
    }

    Tools
    {
        id: tools;
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
            ctx.clearRect(0, 0, canvasWidth, canvasHeight);
            drawCircle(ctx, innerRadius, innerLineWidth, percentInner);
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
        interval: 10;
        repeat: true
        onTriggered:
        {
            canvasCirc.requestPaint();
        }
    }

    Connections
    {
        target: mind;

        onAttentionChanged:
        {
            if(starting)
            {
                percentInner = mind.attention / 100.0;
            }
        }
    }

    Connections
    {
        target: rouletteModule;

        onShowMindwaveControls:
        {
            show();
        }
    }

    function setLocation(x, y)
    {
        canvasCirc.x = x;
        canvasCirc.y = y;
    }

    function setRotation(angle)
    {
        canvasCirc.rotation = angle;
    }

    function show()
    {
        cavasUpdater.running = true;
        visible = true;
        starting = true;
    }

    function hide()
    {
        cavasUpdater.running = false;

        starting = false;
        notifyOnce = false;

        maxAttentionAnim.to = 0;
        maxAttentionAnim.duration = 500;
        maxAttentionAnim.start();
    }

    function drawCircle(ctx, radius, lineWidth, percent)
    {
        ctx.lineCap = lineCap;
        ctx.lineJoin = lineJoin;
        ctx.lineWidth = lineWidth;
        ctx.strokeStyle = colorBg;

        ctx.beginPath();
        ctx.arc(canvasHalfWidth, canvasHalfHeight, radius, 0, 2 * Math.PI * arcPercent);
        ctx.stroke();
        ctx.closePath();

        ctx.strokeStyle = percent > attentionThreshold ? colorInner : colorOuter;

        ctx.beginPath();
        ctx.arc(canvasHalfWidth, canvasHalfHeight, radius, 0, 2 * Math.PI * percent * arcPercent);
        ctx.stroke();
        ctx.closePath();
    }
}

