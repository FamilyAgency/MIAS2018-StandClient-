import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "HealthChecker component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }
       // RowLayout
       // {
        Text
        {
            id:conStatus;
            text: "Arduino health: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "Mindwave health: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:timeText;
            text: "Server health: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
        Text
        {
            id:memoryText;
            text: "Memory health: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
     //   }
    }
}
