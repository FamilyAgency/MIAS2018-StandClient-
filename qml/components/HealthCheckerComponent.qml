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

        ListView {
            width: 180; height: 200

            model: healthChecker.getInfo()
            spacing: 10;
            delegate: Text
            {
                text: modelData
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }
        }
    }
}
