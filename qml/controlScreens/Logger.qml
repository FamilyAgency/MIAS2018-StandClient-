import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item
{
    ColumnLayout
    {
        spacing: 30;

        Text
        {
            text: "Output log";
            font.family: "Helvetica";
            font.pixelSize: 18;
            color: "#009900";
        }

        ScrollView
        {
            id:scroll;
            implicitWidth: 610;
            implicitHeight: 100;

            onHeightChanged:
            {
              // scrollViewToEnd();
            }

            //TextArea
            //{
               // id:__ouputConsole;
//                implicitWidth: 310;
//                implicitHeight: 200;
//                width: 310;
//                height: 200;
//                wrapMode: TextEdit.Wrap;
//                selectByMouse: true;
//                clip: true;
//                textFormat: Text.RichText;
//                font.family: "Helvetica";
//                font.pixelSize: 14;
           // }
        }

        Button
        {
            implicitWidth: 100;
            text: "Clear";
            onClicked:
            {
               ouputConsole.clear();
            }
        }

//        Connections
//        {
//           // target:logger;
////            onLogToOutputConsole:
////            {
////               console.log("-----------", msg);
////               //var color = "red";
////               var richMsg = '<font color=' + color + '>' + msg + '</font>';
////               ouputConsole.append(richMsg);
////            }
//        }
  }
}
