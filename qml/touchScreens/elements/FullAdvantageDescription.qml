import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id:fullAdvantage;

    property string mainTitleDefault: "НАЗВАНИЕ<br/>ПРЕИМУЩЕСТВА";
    property string descrTitleDefault: "Если бы существовал явный механизм экстраполяции струн в низкоэнергетическую физику, то теория струн представила бы нам все фундаментальные частицы и их взаимодействия в виде ограничений на спектры возбуждений нелокальных одномерных объектов. Характерные размеры компактифицированных струн чрезвычайно малы, порядка 10−33 см (порядка планковской длины)[14], поэтому они недоступны наблюдению в эксперименте[2]. Аналогично колебаниям струн музыкальных инструментов спектральные составляющие струн возможны только для определённых частот (квантовых амплитуд). Чем больше частота, тем больше энергия, накопленная в таком колебании[15], и, в соответствии с формулой E=mc², тем больше масса частицы, в роли которой проявляет себя колеблющаяся струна в наблюдаемом мире. Параметром, аналогичным частоте для осциллятора, для струны является квадрат массы[16]"
    property int circleSize : 150;
    property string buttonText: "ПОЕХАЛИ ДАЛЬШЕ";

    signal advantageReaded;

    anchors.fill: parent;
    visible:false;

    Rectangle
    {
        anchors.fill: parent;
        color: "#1c1c1c";
    }

    Text
    {
        id:promtText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 150;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        verticalAlignment :Text.AlignVCenter;
    }

    Text
    {
        id:descrText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: promtText.bottom;
        anchors.topMargin: 50;
        text: descrTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignLeft;
        wrapMode : Text.WordWrap;
        width : 600;
    }

    Button
    {
        id: startBtn;

        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 50;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: buttonText;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle
        {
            implicitHeight: 110;
            implicitWidth: 280;
            color: startBtn.down ? "#3c2755" : "#801bfc";
            radius: 10;
        }

        onClicked:
        {
            fullAdvantage.advantageReaded();
        }
    }

    function setTexts(title, descrText)
    {
        promtText.text = title;
        descrText.text = descrText;
    }

    function show()
    {
        visible = true;
    }

    function hide()
    {
        visible = false;
    }
}
