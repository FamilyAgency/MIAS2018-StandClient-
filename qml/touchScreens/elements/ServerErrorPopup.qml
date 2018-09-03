import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import com.app 1.0

import "../../tools"

Item
{
    id: error;

    property real btnMarginBottom: 305;
    property string errorTitle:  "Ой!<br/>Что-то пошло не так.<br/><br/> Обратитесь за помощью <br/>к промо-персоналу.";
    property string btnTtile: "ПОНЯТНО";

    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    Image
    {
        id: errorBg;
        anchors.fill: parent;
        smooth: true;
        source: "qrc:/resources/Error.png";
    }

    Text
    {
        id: mainText;
        font.family: font.hyundaiSansHeadMedium;
        text: errorTitle;
        font.pixelSize: 60;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top:  parent.top;
        anchors.topMargin: 600;
        horizontalAlignment: Text.AlignHCenter;
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0.0;
    }

    BigRedButton
    {
        id: okBtn;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350;
        btnHeight: 350;
        btnRadius: 175;

        onClicked:
        {
            appController.backToIntro();
            server.freeServer();
            error.visible = false;
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running:false;
        easing.type: "InOutCubic";
    }


    Component.onCompleted:
    {
        visible = false;
        okBtn.setTitle(btnTtile);
    }

    Connections
    {
        target: server;

        onServerRequestError:
        {
            showError();
        }

        onServerGlobalError:
        {
            showError();
        }
    }

//    Connections
//    {
//        target:rfid;

//        onCardReaderError:
//        {
//            switch(error)
//            {

//            case CardReaderError.NoCardReader:
//            case CardReaderError.CantStartTransaction:
//            case CardReaderError.CantEndTransaction:
//            case CardReaderError.LoadKeyError:
//            case CardReaderError.AuthError:
//            case CardReaderError.ReadError:
//            case CardReaderError.UnknownError:
//            case CardReaderError.DataFormatError:
//                showError();
//                break;
//            }
//        }
//    }

    function showError()
    {
        opacity = 0;
        visible = true;
        opacityAnim.start();
        okBtn.show();
    }
}
