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

    SkipLocationTest
    {
       id:skipsLocs;       
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
    }

    Connections
    {
        target:appController;

        onAppStateChanged:
        {
            setState(appState);
        }
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
