import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    Connections
    {
        target: gameTaskManager

        onAllTaskComleteEvent:
        {
            completionText.text = "Completion: " + (gameTaskManager.allTaskCount) + "/" + gameTaskManager.allTaskCount;
        }

        onTaskComleteEvent:
        {
            completionText.text = "Completion: " + (gameTaskManager.currentTaskIndex) + "/" + gameTaskManager.allTaskCount;
        }

        onTaskReset:
        {
            completionText.text = "Completion: " + (gameTaskManager.currentTaskIndex) + "/" + gameTaskManager.allTaskCount;
        }
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "User data";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#000099"
        }

        Text
        {
            text: "Name: " + userData.name;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "Surname: " + userData.surname;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "Id: " + userData.id;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "Clean game task-time: " + gameSession.cleanTime.toFixed(1);
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:stageText;
            text: "Current stage: " +  (gameTaskManager.currentTaskIndex + 1);
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
        Text
        {
            id:completionText;
            text: "Completion: " + (gameTaskManager.currentTaskIndex) + "/" + gameTaskManager.allTaskCount;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
