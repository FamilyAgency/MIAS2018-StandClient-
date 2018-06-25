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
            text: "Stand data";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#000099"
        }
        Text
        {
            text: "Stand Id: " + standData.getStandId();
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#999999";
        }
    }
}
