import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    Connections
    {
        target: gameTaskManager

        onTaskComleteEvent:
        {
           // completionText.text = "Completion: " + (gameTaskManager.currentTaskIndex) + "/" + gameTaskManager.allTaskCount;
        }

        onTaskReset:
        {
          //  completionText.text = "Completion: " + (gameTaskManager.currentTaskIndex) + "/" + gameTaskManager.allTaskCount;
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
            text: "Exist: " + userData.exist;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "First time: " + userData.firstTime;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "Wait enough to play: " + userData.waitEnoughToPlay;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "Finished: " + userData.finished;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            text: "Prizes: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        ListView {
            width: 180; height:50

            model: userData.prizes
            spacing: 1;
            delegate: Text
            {
                text: modelData
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }
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
            id:cleanTimeText;
            text: "Clean game task-time: " + gameProgress.cleanTime.toFixed(1);
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:stageText;
            text: "Current stage: " + gameProgress.currentGameId;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
        Text
        {
            id:completionText;
            text: "Completion: " + gameProgress.gamesCompleteCount + " / " + gameProgress.gamesCount
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
