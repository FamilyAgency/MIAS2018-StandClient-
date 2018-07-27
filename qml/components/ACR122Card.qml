import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{
    Component.onCompleted:
    {
        // console.log("arduino component  ", rfid.config)
    }

    ColumnLayout
    {
        spacing: 10;

        Text
        {
            text: "ACR122Card component";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Text
        {
            id:deviceState;
            text: "State: stopped";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#008800"
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

        TextArea
        {
            implicitWidth: 400;
            implicitHeight: 60;
            id:inputtext;
            width: 310;
            height: 200;
            wrapMode: TextEdit.Wrap;
            selectByMouse: true;
            clip: true;
           // textFormat: Text.RichText;
            font.family: "Helvetica";
            font.pixelSize: 14;
        }
        RowLayout
        {


            Button
            {
                id:write;
                text: "Start Writing"
                onClicked:
                {
                    rfid.startWriting(inputtext.text);
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

        Button
        {
            id:stopAll;
            text: "Stop all"
            onClicked:
            {
                rfid.stopAll();
            }
        }

        Button
        {
            id:beepCommand;
            text: "Beep off"
            onClicked:
            {
                rfid.beepCommand(false);
            }
        }

        Button
        {
            id:attr;
            text: "Format card"
            onClicked:
            {
                rfid.resetCard();
            }
        }

        Text
        {
            id:status;
            text: "Status: ";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#008800"
        }

        Connections
        {
            target:rfid;

            onCardReaderStateChanged:
            {
                switch(state)
                {
                case CardReaderState.Reading:
                    deviceState.text = "State : reading";
                    break;
                case CardReaderState.Writing:
                    deviceState.text = "State : writing";
                    break;
                case CardReaderState.Stopped:
                    deviceState.text = "State : stopped";
                    break;
                }
            }

            onNoCard:
            {
                status.text = "Status: no card";
            }

            onNoCardReader:
            {
                status.text = "Status: no card reader";
            }

            onAuthError:
            {
                status.text = "Status: on auth error";
            }

            onUnknownError:
            {
                 status.text = "Status: unknown error";
            }

            onReadingCardError:
            {
                 status.text = "Status: on reading card error";
            }

            onNewData:
            {
                 status.text = "Status: new data " + data;
            }

            onNewTag:
            {
                 status.text = "Status: new tag " + id;
            }

            onUserWriteSuccess:
            {
                 status.text = "Status: on User Write Status: Success";
            }

            onUserWriteError:
            {
                status.text = "Status: on User Write Status: Error";
            }
        }
    }
}
