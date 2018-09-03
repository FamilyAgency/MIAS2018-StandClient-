import QtQuick 2.0

import "../../tools"

Item
{
    Consts
    {
        id:consts;
    }

    Image
    {
        id: donate;
        source: "qrc:/resources/finish.png";
    }

    AnimationPlayer
    {
        id: flag;
        currentImage: 1;
        endFrame: 72;
        startFrame: 1;
        Component.onCompleted:
        {
            flag.setSource("content/misc/flag/", ".png");
            flag.setFPS(30);
            flag.init();
        }
    }

    function show()
    {
        visible = true;
    }

    function hide()
    {
        visible = false;
    }

    function setFlagPosition(x, y)
    {
        flag.setLocation(x - 10, y - 66);
        donate.x = x - 16;
        donate.y = y - 16;
    }
}
