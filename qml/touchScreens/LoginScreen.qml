import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item {

    id:login
    anchors.fill: parent
    anchors.centerIn: parent

    Connections
    {
        target:loginModule;
        onLoginStateChanged:
        {
            switch(loginState)
            {
            case LoginState.Login:
                mainText.text = "О привет, " + userData.name + "! Начнем!";
                startBtn.visible = true;
                break;
            }
        }
    }

    function reset()
    {
        mainText.text =  "Привет. Приложи браслет, чтобы начать";
        erroText.visible = false;
        startBtn.visible = false;
    }

    function setTestState(state)
    {
        reset();
    }

    ColumnLayout
    {
        spacing: 10;
        anchors.centerIn: parent
        Text
        {
            id:mainText;
            Layout.alignment : Qt.AlignHCenter
            text: "Привет. Приложи браслет, чтобы начать";
            font.family: "Helvetica"
            font.pixelSize: 25
            color: "#999999"
        }

        Text
        {
            id:erroText;
            Layout.alignment : Qt.AlignHCenter
            visible : false;
            text: "Не знаю кто ты человек";
            font.family: "Helvetica"
            font.pixelSize: 20
            color: "#990000"
        }

        Button
        {
            id: startBtn
            Layout.alignment : Qt.AlignHCenter
            text:"Start"
            visible:false
            onClicked:
            {
                appController.startInstruction();
            }
        }
    }
}
