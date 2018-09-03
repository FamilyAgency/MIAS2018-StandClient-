import QtQuick 2.0
import QtQuick.Particles 2.0
import QtGraphicalEffects 1.0

Item
{
    anchors.fill: parent;

    ParticleSystem
    {
        id:particleSystem;

        anchors.fill: parent;

        ImageParticle
        {
            groups: ["A"];
            anchors.fill: parent;
            source: "qrc:/resources/Round.png";
            color:"#FF1010";
            redVariation: 0.8;
        }

        ImageParticle
        {
            groups: ["B"];
            anchors.fill: parent;
            source: "qrc:/resources/Round.png";
            color:"#336aee";
        }

        ImageParticle
        {
            groups: ["C"];
            anchors.fill: parent;
            source: "qrc:/resources/Round.png";
            color:"#ffffff";
        }


        Emitter
        {
            group: "C";
            emitRate: 20;
            lifeSpan: 2800;
            size: 2;
            sizeVariation: 2;
            velocity: PointDirection{ x: -86; xVariation: 20; }
            width: parent.width;
            height: parent.height;
        }


        Emitter
        {
            group: "A";
            emitRate: 100;
            lifeSpan: 2800;
            size: 2;
            sizeVariation: 10;
            velocity: PointDirection{ x: -66; xVariation: 20; }
            width: parent.width;
            height: parent.height;
        }

        Emitter
        {
            group: "B";
            emitRate: 50;
            lifeSpan: 2800;
            size: 2;
            sizeVariation: 4;
            velocity: PointDirection{ x: -86; xVariation: 20; }
            width: parent.width;
            height: parent.height;
        }

        FastBlur
        {
            anchors.fill: parent;
            source: particleSystem;
            radius: 50;
        }
    }
}
