import QtQuick 2.0

Item
{
    anchors.fill: parent;

    AnimatedSprite
    {
        x: 100;
        y: 100;
        source: configController.getFileInAppDir("content/data/stand1/animations/santa.png");
        frameWidth:128
        frameHeight:210

        running: true
        frameCount: 9
        frameDuration: 60
        width:128
        height:210
    }

    AnimatedSprite
    {
        x: 500;
        y: 500;
        source: configController.getFileInAppDir("content/data/stand1/animations/santa-death.png");
        frameWidth:236
        frameHeight:270

        running: true
        frameCount: 11
        frameDuration: 60
        width:236
        height:270
    }
}
