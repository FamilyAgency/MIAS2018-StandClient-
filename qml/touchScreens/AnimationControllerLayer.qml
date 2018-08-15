import QtQuick 2.0
import QtQuick.Controls 2.1

Item
{
    id: anim;
    anchors.fill: parent;

    Rectangle
    {
        color: "white";
        anchors.fill: parent;
        opacity: 0.0;
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0.0;
    }

    function show()
    {
        visible = true;
    }

    function hide()
    {
        visible = false;
    }
}
