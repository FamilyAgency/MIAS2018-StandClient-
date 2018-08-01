import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

ApplicationWindow
{
    title: qsTr("FileReader")
    x: 20;
    y: 0;
    width: 500;
    height: 700;
    visible: true;

    id: core;

    ColumnLayout
    {
        spacing: 10;

        ScrollView
        {
            implicitWidth: 500;
            implicitHeight: 200;

            TextArea
            {
                id: textReaded
                width: 310;
                height: 200;
                wrapMode: TextEdit.Wrap;
                selectByMouse: true;
                clip: true;
                textFormat: Text.RichText;
                font.family: "Helvetica";
                font.pixelSize: 14;
            }
        }

        Button
        {
            text: "Read File"
            onClicked:
            {
                textReaded.text = fileReader.read("content/rules.txt");
            }
        }
    }

    Connections
    {
        target: fileReader;

        onReadError:
        {
            console.log(error);
        }
    }
}
