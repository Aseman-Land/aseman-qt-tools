import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import "../global"

Rectangle {
    color: masterPalette.window
    clip: true

    TextField {
        id: filterBar
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10*Devices.density
        placeholderText: qsTr("Filter...")
    }

    AsemanListView {
        id: listv
        width: parent.width
        anchors.top: filterBar.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 10*Devices.density
        clip: true
        model: CountriesModel {
            filter: filterBar.text
        }

        delegate: MainMenuItem {
            width: listv.width
            text: "%1 (+%2)".arg(model.name).arg(model.callingCode)
        }
    }

    PhysicalScrollBar {
        anchors.right: listv.right
        anchors.top: listv.top
        height: listv.height
        width: 6*Devices.density
        color: masterPalette.highlight
        scrollArea: listv
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("CountriesModel")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
