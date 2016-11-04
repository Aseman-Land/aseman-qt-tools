import QtQuick 2.7
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {

    NetworkSleepManager {
        id: nwsManager
        host: "aseman.co"
        port: 80
        interval: 5000
        networkManager: true
    }

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        ColumnLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            Label {
                text: nwsManager.available? "Network Available" : "Network Unreachable"
                color: nwsManager.available? "#009900" : "#990000"
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("NetworkSleepManager")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
