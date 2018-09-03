import QtQuick 2.0

MouseArea
{
	width: 100;
	height: 100;

	anchors.top: parent.top;
	anchors.right: parent. right;
	anchors.topMargin: 50;
    anchors.rightMargin: 0;

	Image
	{
		source: "qrc:/resources/Close.png"
	}
}
