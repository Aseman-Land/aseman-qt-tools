import QtQuick 2.0
import AsemanTools 1.0

Item {
    id: item
    width: parent.width
    height: 50*Devices.density

    property alias text: txt.text

    signal clicked()

    Rectangle {
        anchors.fill: parent
        color: masterPalette.highlight
        opacity: marea.pressed? 0.3 : 0
        Behavior on opacity {
            NumberAnimation{easing.type: Easing.OutCubic; duration: 400}
        }
    }

    Text {
        id: txt
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 10*Devices.fontDensity
        x: View.layoutDirection==Qt.LeftToRight? 20*Devices.density : parent.width - width - 10*Devices.density
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onClicked: item.clicked()
    }

    Rectangle {
        width: parent.width
        anchors.bottom: parent.bottom
        height: 1
        color: "#cccccc"
    }
}
