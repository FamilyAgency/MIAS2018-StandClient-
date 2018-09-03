import QtQuick 2.0
import "../../tools"

Text
{
	anchors.left: parent.left;
	anchors.right: parent.right;
	font.family: font.hyundaiSansHeadRegular;
	font.pixelSize: 30;
	wrapMode: Text.Wrap;
	color: "white";

	FontManager
	{
		id: font;
	}
}
