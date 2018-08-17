import QtQuick 2.0
import QtQuick.Controls 2.2
import "../../tools"

Button
{
	id: citiesBtn;

	property string btnColor: "#112041";
	property string btnText: "Выбери меня";
	property int choosenIndex: -1;

	signal indexChanged();

	text: btnText;

	anchors.left: parent.left;
	anchors.right: parent.right;

	contentItem: Text
	{
		text: parent.text;
		font.family: font.hyundaiSansHeadLight;
		font.pixelSize: 30;
		color: "#fff";
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		elide: Text.ElideRight
	}

	background: Rectangle
	{
		implicitWidth: 500;
		implicitHeight: 150;
		radius: 100;
		color: "#000";
		border.color: btnColor;
	}

	FontManager
	{
		id: font;
	}

	function clear()
	{
		choosenIndex = -1;
	}

	function setIndex(index)
	{
		choosenIndex = index;
		indexChanged();
	}
}
