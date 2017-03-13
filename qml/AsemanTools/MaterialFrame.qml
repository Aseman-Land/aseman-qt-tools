import AsemanTools 1.1
import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {

    property alias color: backFrame.color
    property alias radius: backFrame.radius

    DropShadow {
        anchors.fill: source
        cached: true
        horizontalOffset: 1*Devices.density
        verticalOffset: 1*Devices.density
        radius: 6*Devices.density
        samples: 16
        color: "#30000000"
        source: scene
    }

    Item {
        id: scene
        anchors.fill: parent
        anchors.margins: -5*Devices.density

        Rectangle {
            id: backFrame
            anchors.fill: parent
            anchors.margins: 5*Devices.density
            radius: 3*Devices.density
        }
    }
}
