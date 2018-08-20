import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../../components"
import "../../touchScreens/elements"
import "../../touchScreens"
import "../../tests"
import com.app 1.0

Item
{
    id:screens;

    property var locations: [];

    anchors.fill: parent;

    Button
    {
        id: hideBtn;
        text: "";
        visible: true;
        width: 100;
        height: 100;
        anchors.top: parent.top;
        anchors.topMargin: 0;
        anchors.left: parent.left;
        anchors.leftMargin: 100;
        opacity: 0.0;
        onClicked:
        {
           toggleTestInterface();
        }
    }

    SkipLocationTest
    {
        id:skipsLocs;
    }

    MonitoringComponent
    {
        id:monitoringComp;
    }

    MindwaveComponent
    {
        id: mindWaveComp;
        x: 50;
        y: 260;
    }

    Component.onCompleted:
    {
        addLocation(AppState.Intro, "IntroScreenTest");
        addLocation(AppState.SuperGame, "SuperGameScreenTest");
        setState(appController.getAppState());
        toggleTestInterface();
    }

    Connections
    {
        target:appController;

        onAppStateChanged:
        {
            setState(appState);
        }
    }

    function toggleTestInterface()
    {
        skipsLocs.visible = !skipsLocs.visible;
        mindWaveComp.visible = !mindWaveComp.visible;
        monitoringComp.visible = !monitoringComp.visible;
    }

    function addLocation(type, component)
    {
        var componentQML = Qt.createComponent(component + ".qml");
        var location = componentQML.createObject(screens);
        locations.push({"loc": location, "type": type});
    }

    function setState(appState)
    {
        hideAll();

        for(var i = 0; i < locations.length; i++)
        {
            if(locations[i].type === appState)
            {
                locations[i].loc.start();
                break;
            }
        }
    }

    function hideAll()
    {
        for(var i = 0; i < locations.length; i++)
        {
            locations[i].loc.stop();
        }
    }
}
