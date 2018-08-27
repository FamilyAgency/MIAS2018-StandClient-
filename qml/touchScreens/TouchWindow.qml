import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../components"
import "elements"
import com.app 1.0

import "game"
Item
{
    id: touchCore;
    anchors.fill: parent;
    anchors.centerIn: parent;

    property var locations: [];

    VideoManager
    {
        id: videos;
    }

    Item
    {
        id: screens;
        anchors.fill: parent;
        z: 3;
    }

    HealthCheckerComponent
    {
        id:health;
        x: 50;
        visible: false;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 200;
        z: 4;
    }

    ServerPreloader
    {
        id: serverPreloader;
        z: 4;
    }

    AnimationControllerLayer
    {
        id: animationController;
        z: 4;
    }

    Indicators
    {
        id: indicators;
    }

    ServerErrorPopup
    {
        id: serverErrorPopup;
        z: 4;
    }

    SecretBackBtn
    {
        id: backBtn;
        z: 4;
    }

    SecretCloseBtn
    {
        id: closeBtn;
        z: 4;
    }

    MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            focusedId.forceActiveFocus();
        }
    }

    Item
    {
        id:focusedId;
        focus: true;
        anchors.fill: parent;

        Keys.onPressed:
        {
            if (event.key === Qt.Key_Escape)
            {
                Qt.quit();
            }
        }
    }


    //     AdvantageDescription
    //     {
    //         id:a;
    //         Component.onCompleted:
    //         {
    //             a.setTexts("Довезёт и до города<br/> Санта-Фе, и до Санта<br/> Клауса!","Сила мысли — это хорошо! А 200-сильный<br/>двигатель с 8-ступенчатой АКПП — лучше.<br/>8-ступенчатая коробка-автомат — это восемь<br/>степеней свободы на любой дороге.<br/>А в качестве приятного бонуса к комфортному<br/>вождению — экономия топлива!")
    //             a.setTexts("Полный привод —<br/>едем с умом!","Система HTRAC анализирует, по какой дороге<br/>едет автомобиль, и автоматически распределяет<br/>нагрузку между осями. Она помогает проходить<br/>повороты безопаснее, и ехать по городу<br/>и бездорожью одинаково легко.")
    //             a.setTexts("Нет безвыходных<br/>ситуаций. Есть<br/> безопасный выход!","Если сзади приближается другой автомобиль,<br/>система безопасного выхода предупредит<br/>об опасности и не даст разблокировать задние<br/>двери, чтобы пассажиры остались в салоне.")
    //             a.setTexts(" Весь экипаж <br/>под присмотром!"," Специальный датчик определяет, <br/>есть ли кто-нибудь на задних сидениях, <br/>чтобы водитель не забыл в салоне <br/>даже самого маленького пассажира. ")
    //             a.setTexts(" Глядеть по сторонам — <br/>это и наша забота!"," Ещё одна умная система защитит<br/> при выезде задним ходом с парковки: <br/>она «увидит» автомобиль, двигающийся<br/>наперерез, предупредит об этом и даже<br/>самостоятельно остановит Hyundai SANTA FE<br/> при необходимости. ")
    //             a.setTexts("Всё самое важное — <br/> на лобовом стекле!","Данные о скорости движения, <br/>  подсказки умных систем безопасности<br/>и навигации проецируются прямо<br/>на лобовое стекло. Так что вся информация — <br/>прямо перед глазами водителя. ")
    //             a.setTexts("Когда каждое место <br/>на борту —  самое удобное!","Чтобы  попасть на третий  ряд сидений, <br/> достаточно нажать на кнопку. Чтобы<br/>сложить второй ряд — тоже. Так вы<br/>всегда можете выбрать наиболее удобную<br/>схему расположения пассажирских сидений. ")
    //             a.setVideo("1")
    //             a.show();
    //         }
    //     }




    Component.onCompleted:
    {
        addLocation(AppState.Intro, "IntroScreen");
        addLocation(AppState.Instruction, "InstructionScreen");
        addLocation(AppState.Roulette, "RouletteScreen");
        addLocation(AppState.Game, "GameScreen");
        addLocation(AppState.GameResult, "GameResultScreen");
        addLocation(AppState.SuperGame, "SuperGameScreen");
        addLocation(AppState.SuperGameResult, "SuperGameResultScreen");
        addLocation(AppState.TestDrive, "TestDriveScreen");

        setState(appController.getAppState());
    }

    Connections
    {
        target: appController;

        onAppStateChanged:
        {
            console.log("touch app state changes :::::::::::::", appState);
            setState(appState);
        }
    }

    function addLocation(type, component)
    {
        var componentQML = Qt.createComponent(component + ".qml");
        var location = componentQML.createObject(screens);
        location["onAnimComplete"].connect(function() { onAnimComplete() });
        location["onAnimStart"].connect(function() { onAnimStart() });
        locations.push({"loc": location, "type": type});
    }

    function setState(appState)
    {
        hideAll();
        animationController.show();

        for(var i = 0; i < locations.length; i++)
        {
            if(locations[i].type === appState)
            {
                locations[i].loc.start();
                break;
            }
        }
    }

    function onAnimComplete()
    {
        animationController.hide();
    }

    function onAnimStart()
    {
        animationController.show();
    }

    function hideAll()
    {
        for(var i = 0; i < locations.length; i++)
        {
            locations[i].loc.stop();
        }
    }
}
