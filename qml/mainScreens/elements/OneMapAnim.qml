import QtQuick 2.0

Item
{
    id: animationItem
    anchors.fill: parent;

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
            duration: 1000
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
        anim.start();
    }
}
