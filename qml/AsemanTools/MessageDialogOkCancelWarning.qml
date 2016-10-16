import QtQuick 2.0
import AsemanTools 1.0

Column {
    id: column
    anchors.verticalCenter: parent.verticalCenter
    anchors.left: parent.left
    anchors.right: parent.right
    spacing: 10*Devices.density

    property alias message: msg.text

    signal canceled()
    signal ok()

    Item {width: 1; height: 1}

    Text {
        id: msg
        width: column.width - 60*Devices.density
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: AsemanApp.globalFont.family
        font.pixelSize: 9*Devices.fontDensity
        color: "#333333"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 10*Devices.density

        Button {
            textFont.family: AsemanApp.globalFont.family
            textFont.pixelSize: 10*Devices.fontDensity
            textColor: "#0d80ec"
            normalColor: "#00000000"
            highlightColor: "#660d80ec"
            text: qsTr("Cancel")
            radius: 3*Devices.density
            onClicked: {
                column.canceled()
                AsemanApp.back()
            }
        }

        Button {
            textFont.family: AsemanApp.globalFont.family
            textFont.pixelSize: 10*Devices.fontDensity
            textColor: "#0d80ec"
            normalColor: "#00000000"
            highlightColor: "#660d80ec"
            text: qsTr("OK")
            radius: 3*Devices.density
            onClicked: column.ok()
        }
    }
}
