import QtQuick 2.0

import "../../tools"

Text
{
	anchors.left: parent.left;
	anchors.right: parent.right;
	font.family: font.hyundaiSansHeadMedium;
	font.pixelSize: 80;
	wrapMode: Text.Wrap;
	color: "white";

	FontManager
	{
		id: font;
	}
}
