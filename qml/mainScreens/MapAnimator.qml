import QtQuick 2.0

import "elements"

Item
{
    id: animHolder;
    anchors.fill: parent;

    Component.onCompleted:
    {
        var animations = animationManager.getAnimations();

        for(var i = 0; i < animations.length; i++)
        {
            var componentQML = Qt.createComponent("elements/OneMapAnim.qml");
            var oneAnim = componentQML.createObject(animHolder);
            oneAnim.setData(animations[i]);
        }
    }
}
