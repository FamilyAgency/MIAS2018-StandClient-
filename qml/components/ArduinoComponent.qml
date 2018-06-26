import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    Component.onCompleted:
    {
        console.log("arduino component  ", arduino.config)
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Arduino component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Text
        {
            id:com;
            text: "COM: " + arduino.config.serialPort;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:baudRate;
            text: "Baud rate: " + arduino.config.baudRate;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:conStatus;
            text: "Serial connection status: " + arduino.connected;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "Arduino data: 0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
