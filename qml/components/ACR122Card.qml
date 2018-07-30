import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.app 1.0

ApplicationWindow
{
    visible: true;
    width: 500;
    height: 700;
    x: 20;
    y: 0;
    title: qsTr("RFID");
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
            font.family: "Helvetica";
            font.pixelSize: 17;
            color: "#008800";
        }

        Text
        {
            id:deviceState;
            text: "State: stopped";
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#008800";
        }

        Text
        {
            id:errorText;
            text: "Last error: ";
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#008800";
        }

        Text
        {
            id:validation;
            text: "Validation: ";
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#008800";
        }

        Button
        {
            id:readId;
            text: "Start Reading Id only";
            onClicked:
            {
                rfid.startReadingId();
            }
        }

        Button
        {
            id:readAll;
            text: "Start Reading All data";
            onClicked:
            {
                rfid.startReadingAllData();
            }
        }

        TextField
        {
            id: name;
            placeholderText: "name";
            text: "Иван";
            implicitWidth:200;
        }

        TextField
        {
            id:surname;
            placeholderText: "surname";
            text: "Иванов";
            implicitWidth:200;
        }

        TextField
        {
            id:phone;
            placeholderText: "phone";
            text: "89067895699";
            implicitWidth:200;
        }

        TextField
        {
            id:mail;
            placeholderText: "mail";
            text: "почта@яндекс.ру";
            implicitWidth:200;
        }

        SpinBox
        {
            id: rfidBox;
            value: 1000;
            from: 0;
            to: 2000;
            editable: true;
        }

        RowLayout
        {
            Button
            {
                id:write;
                text: "Start Writing"
                onClicked:
                {
                    rfid.startWriting(rfidBox.value, name.text, surname.text, phone.text, mail.text);
                }
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
        RowLayout
        {
            Button
            {
                id:beepCommand;
                text: "Beep"
                onClicked:
                {
                    rfid.beepCommand(beepEnabled.checked);
                }
            }

            CheckBox
            {
                id:beepEnabled;
                text: qsTr("enabled")
                checked: false
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
            font.family: "Helvetica";
            font.pixelSize: 14;
        }

        Component.onCompleted:
        {
            clearError();
        }

        Connections
        {
            target:rfid;

            onCardReaderStateChanged:
            {
                switch(state)
                {
                case CardReaderState.Reading:
                    deviceState.text = "State: reading";
                    break;
                case CardReaderState.Writing:
                    deviceState.text = "State: writing";
                    break;
                case CardReaderState.Stopped:
                    deviceState.text = "State: stopped";
                    break;
                case CardReaderState.Validating:
                    deviceState.text = "State: validating";
                    break;
                }
            }
            
            onCardReaderError:
            {
                console.log("Card ReaderError", error);
                errorText.text = "Last error: " + error;
                errorText.color = "#990000";

                switch(error)
                {
                case CardReaderError.CantStartTransaction:
                    break;
                case CardReaderError.CantEndTransaction:
                    break;
                case CardReaderError.LoadKeyError:
                    break;
                case CardReaderError.NoCardReader:
                    break;
                case CardReaderError.NoCard:
                    errorText.text = "Last error: no card near";
                    break;
                case CardReaderError.AuthError:
                    break;
                case CardReaderError.WriteError:
                    break;
                case CardReaderError.ReadError:
                    break;
                case CardReaderError.UnknownError:
                    break;
                }
            }

            onValidationSuccess:
            {
                clearError();
                validation.text = "Validation: success";
            }

            onValidationFailed:
            {
                clearError();
                validation.text = "Validation: failed";
            }

            onUserReadSuccess:
            {
                clearError();
                outputtext.text = "New data: " + data;
            }

            onUserWriteSuccess:
            {
                clearError();
                outputtext.text = "Status: on write success";
            }
        }
    }

    function clearError()
    {
        errorText.text = "Error: no error";
        errorText.color = "#009900";
    }

    Connections
    {
        target:server;
        onServerRequestSuccess:
        {
            switch(responseType)
            {
            case ResponseType.CreateUserRequest:
                rfidBox.value = userData.baseUserData.id;
                name.text = userData.baseUserData.name;
                surname.text = userData.baseUserData.surname;
                phone.text = userData.baseUserData.phone;
                mail.text = userData.baseUserData.email;
                break;
            }
        }
    }
}
