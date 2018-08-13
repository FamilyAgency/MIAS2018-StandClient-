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

    property string superGameTitle: "ПОЗДРАВЛЯЕМ";
    property string descrTitleDefault: "Прямо сейчас<br/>на стойке выдаче<br/>подарков вас ждет<br/>бесплатный подарок";
    property string btntext: "ЗАПИСАТЬСЯ<br/>НА ТЕСТ-ДРАЙВ";
    property real btnMarginBottom: 100 * consts.designScale;


    signal gotoIntro();

    FontManager
    {
        id:font;
    }

    Consts
    {
        id: consts;
    }

    TitleBlock
    {
        id: title;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

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
        backBtn.hide();
        title.hide();
        brb.hide();
    }
}
