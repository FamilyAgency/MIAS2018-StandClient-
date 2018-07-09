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
            text: "Server component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Text
        {
            id:url;
            text: "Url: " + server.serverConfig.url;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:response;
            text: "Last response: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
