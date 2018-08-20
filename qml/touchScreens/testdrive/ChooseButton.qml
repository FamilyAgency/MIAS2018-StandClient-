import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

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
		//border.color: btnColor;
	}

	layer.enabled: true;
	layer.effect: Glow
	{
		radius: 150;
        samples: 200;
        color: btnColor + "66";
		transparentBorder: true;
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
