import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../elements"
import "../../tools"
Item
{
    id: result;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string superGameTitle: "";
    property string descrTitleDefault: "Вы были близки к победе. <br/><br/>Попробуйте еще раз<br/> через 20 минут. <br/>Вам обязательно повезет!";
    property string btntext: "ЗАПИСАТЬСЯ<br/>НА ТЕСТ-ДРАЙВ";
    property real btnMarginBottom: 100;

    signal gotoIntro();

    TitleBlock
    {
        id: title;
        offsetY: 400;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350;
        btnHeight: 350;
        btnRadius: 175;

        onClicked:
        {
            result.gotoIntro();
        }
    }

    SimpleButton
    {
        id: backBtn;
        anchors.top: brb.bottom;
        anchors.fill: parent;
        onClicked:
        {
            appController.backToIntro();
        }
    }

    Component.onCompleted:
    {
        title.setTexts(superGameTitle, descrTitleDefault);
        brb.setTitle(btntext);
    }

    function show()
    {
        title.show();
        backBtn.show();       
        brb.show();
    }

    function hide()
    {
        title.hide();
        brb.hide();
        backBtn.hide();
    }
}
