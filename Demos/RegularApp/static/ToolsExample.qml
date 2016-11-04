import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import "../global"

Rectangle {
    color: masterPalette.window
    clip: true

    AsemanFlickable {
        id: flick
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        contentWidth: column.width
        contentHeight: column.height

        Column {
            id: column
            width: flick.width

            MainMenuItem {
                text: "Visit Documents on Github"
                onClicked: Qt.openUrlExternally("https://github.com/Aseman-Land/aseman-qt-tools/blob/master/documents/tools.md")
            }
        }
    }

    PhysicalScrollBar {
        anchors.right: flick.right
        anchors.top: flick.top
        height: flick.height
        width: 6*Devices.density
        color: masterPalette.highlight
        scrollArea: flick
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Tools")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
