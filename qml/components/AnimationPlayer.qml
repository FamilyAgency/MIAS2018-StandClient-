import QtQuick 2.0
import "../tools"
Item
{
    id: animationItem
    anchors.fill: parent;
    property int currentImage: 1;
    property int startFrame: 1;
    property int endFrame: 1;

    Consts
    {
        id:consts;
    }

    Image
    {
        id: image;
        x: 0;
        y: 0;
    }

    NumberAnimation on currentImage
    {
        id: animAnim;
        from: startFrame;
        to: endFrame
        duration: 2000
        running: false;
        loops: Animation.Infinite;
    }

    function setFPS(fps)
    {
        animAnim.duration = (endFrame - startFrame) * 1000.0 / fps;
    }

    function setSource(path, ext)
    {
        image.source = Qt.binding(function()
        {
            return configController.getFileInAppDir( path + currentImage + ext);
        });
    }

    function init()
    {
        animAnim.duration = (endFrame - startFrame) * 1000.0 / consts.animFPS;
        animAnim.start();
    }

    function setLocation(x, y)
    {
        image.x = x;
        image.y = y;
    }

    function setRunning(value)
    {
        animAnim.running = value;
    }
}
