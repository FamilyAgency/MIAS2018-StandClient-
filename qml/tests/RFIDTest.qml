import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../mainScreens"

Item
{
    id: rfidTest;

    Consts
    {
        id:consts;
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "RFID Test";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: consts.infoTextColor
        }

        RowLayout
        {
            spacing: 10;
            Button
            {
                text:"RFID entered: "
                onClicked:
                {
                    rfid.testDataCome(rfidBox.value);
                }
            }

            SpinBox
            {
                id: rfidBox
                value: 1000
                from: 0
                to: 2000
                editable: true
            }
        }
    }
}
