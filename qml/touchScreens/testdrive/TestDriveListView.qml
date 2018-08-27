import QtQuick 2.0
import QtQuick.Controls 2.2

import "../../tools"


ListView
{
	id: listView;

    property string titleText;
    property string subTitleText;

	signal itemChoosen(int index);

	model: ["none"];

	anchors.fill: parent;
	anchors.leftMargin: 200;
	anchors.rightMargin: 200;

	delegate: listItem;
	header: headerItem;
	footer: footerItem;
	section
	{
		property: "modelData";
		criteria: ViewSection.FirstCharacter;
		delegate: sectionItem;
	}

	Component
	{
		id: headerItem;

		Item
		{
			width: parent.width;
			height: 370;
			y: 150;

			MediumText
			{               
                text: titleText;
                font.pixelSize: 60;
				anchors.top: parent.top;
				anchors.topMargin: 100;
			}

			RegularText
			{
                text:subTitleText;
				font.pixelSize: 38;
				anchors.top: parent.top;
				anchors.topMargin: 250;
				wrapMode: Text.Wrap;
			}
		}
	}

	Component
	{
		id: sectionItem;

		Item
		{
			height: 165;
			width: parent.width;
			MediumText
			{
				height: parent.height;
				anchors.fill: parent;
				verticalAlignment: Text.AlignBottom;
				text: section;
				font.pixelSize: 60;
				color: "#0893b7";
			}
		}
	}

	Component
	{
		id: listItem;

		Item
		{
		   anchors.left: parent.left;
		   anchors.right: parent.right;
		   width: parent.width;
		   height: 120;

		   RegularText
		   {
				text: modelData;
				font.pixelSize: 24;
				verticalAlignment: Text.AlignVCenter;
				anchors.fill: parent;
		   }

		   Rectangle
		   {
			   anchors.left: parent.left;
			   anchors.right: parent.right;
			   anchors.bottom: parent.bottom;
			   height: 1;
			   color: "#fff";
			   opacity: 0.1;
		   }
		   MouseArea
		   {
			   anchors.fill: parent;
			   onClicked:
			   {
				   itemChoosen(index);
			   }
		   }
		}
	}

	Component
	{
		id: footerItem;
		Item
		{
			height: 500;
		}
	}

	FontLoader
	{
		id: font;
	}

}
