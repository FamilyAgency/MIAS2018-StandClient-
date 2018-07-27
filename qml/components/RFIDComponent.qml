import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    Component.onCompleted:
    {
       // console.log("arduino component  ", rfid.config)
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "RFID component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }
        RowLayout
        {

            ComboBox
            {
                id:comComboBox;
                Component.onCompleted:
                {
                    //com.text = "Selected: " + currentText;
                }

                width: 200
                model: rfid.getPortsAvailable();
                onCurrentIndexChanged: {
                   // rfid.startReading(1);
                    //com.text = "Selected: " + currentText;
                   }
            }

//            Text
//            {
//                id:com;
//                text: "Selected : " + rfid.config.serialPort;
//                font.family: "Helvetica"
//                font.pixelSize: 15
//                color: "#999999"
//                wrapMode: Text.WordWrap
//                clip: true
//            }
            Button
            {
                id:con;
                text: "connect"
                onClicked:
                {
                    rfid.startReading(comComboBox.currentIndex);
                }
            }

            Button
            {
                id:read;
                text: "Start Reading"
                onClicked:
                {
                    rfid.startReading();
                }
            }

        }

        Text
        {
            id:autoCon;
            text: "Auto connect: " + rfid.rfidConfig.autoConnect;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:baudRate;
            text: "Baud rate: " + rfid.rfidConfig.baudRate;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:conStatus;
            text: "Serial connection status: " + rfid.connected;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "RFID data: 0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
