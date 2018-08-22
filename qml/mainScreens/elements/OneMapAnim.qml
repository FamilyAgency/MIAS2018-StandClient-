import QtQuick 2.0
import "../../tools"
Item
{
    id: animationItem
    anchors.fill: parent;

    Consts
    {
        id:consts;
    }

    Image
    {
        property int currentImage: 1;
        id: image;
        x: 0;
        y: 0;

        NumberAnimation on currentImage
        {
            id: anim;
            from: 1;
            to: 35
            duration: 2000
            running: false;
            loops: Animation.Infinite;
        }
    }

    function setData(data)
    {
        image.source = Qt.binding(function()
        {
            return standData.getStandImage( "animations/" + data.path + "/"+ image.currentImage + ".png")
        });
        image.x = data.x;
        image.y = data.y;
        anim.to = data.frames;
        anim.duration = anim.to * 1000.0 / consts.animFPS;
        anim.start();
    }
}
