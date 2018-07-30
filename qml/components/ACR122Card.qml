import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.app 1.0

ApplicationWindow
{
    visible: true;
    width: 500;
    height: 600;
    x: 420;
    y: 60;
    title: qsTr("App");
    id: core;

    Component.onCompleted:
    {
        // console.log("arduino component  ", rfid.config)
    }

    ColumnLayout
    {
        x: 50;
        y: 50;
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
            id:readId;
            text: "Start Reading Id only"
            onClicked:
            {
                rfid.startReadingId();
            }
        }

        Button
        {
            id:readAll;
            text: "Start Reading All data"
            onClicked:
            {
                rfid.startReadingAllData();
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
                    rfid.startWriting(9910, "юрий", "попович", "79065678789", "яндекс@мейл.ру");
                    //rfid.startWriting(inputtext.text);
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

        TextArea
        {
            implicitWidth: 400;
            implicitHeight: 60;
            id:outputtext;
            width: 310;
            height: 200;
            wrapMode: TextEdit.Wrap;
            selectByMouse: true;
            clip: true;
           // textFormat: Text.RichText;
            font.family: "Helvetica";
            font.pixelSize: 14;
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

//            onNoCard:
//            {
//                status.text = "Status: no card";
//            }

//            onNoCardReader:
//            {
//                status.text = "Status: no card reader";
//            }

//            onAuthError:
//            {
//                status.text = "Status: on auth error";
//            }

//            onUnknownError:
//            {
//                 status.text = "Status: unknown error";
//            }

//            onReadingCardError:
//            {
//                 status.text = "Status: on reading card error";
//            }

            onValidationSuccess:
            {
                console.log("validation success");
            }

            onValidationFailed:
            {
                console.log("validation failed");
            }

            onUserReadSuccess:
            {
                 outputtext.text = "Status: new data " + data;
            }

            onUserWriteSuccess:
            {
                 outputtext.text = "Status: on User Write Status: Success";
            }

//            onUserWriteError:
//            {
//                status.text = "Status: on User Write Status: Error";
//            }
        }
    }
}
