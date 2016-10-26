import QtQuick 2.7
import AsemanTools 1.0

Rectangle {
    color: masterPalette.highlight

    Rectangle {
        id: rect
        color: masterPalette.window
        anchors.fill: parent

        MainPage {
            width: parent.width
            anchors.top: header.bottom
            anchors.bottom: parent.bottom
        }

        Header {
            id: header
            width: parent.width
            color: masterPalette.highlight
            text: qsTr("MenuController")
            shadow: true
        }
    }

    MenuController {
        id: menuController
        anchors.fill: parent
        source: rect
        component: Item {
            anchors.fill: parent

            ListView {
                id: view
                model: 5
                width: parent.width - 40*Devices.density
                height: parent.height - 300*Devices.density
                anchors.centerIn: parent
                delegate: Item {
                    width: view.width
                    height: 40*Devices.density
                    Text {
                        x: View.layoutDirection==Qt.LeftToRight? 20*Devices.density : parent.width - width - 10*Devices.density
                        text: "Item " + index
                        color: "#ffffff"
                    }
                }
            }
        }
    }

    HeaderMenuButton {
        ratio: menuController.ratio
        buttonColor: "white"
        onClicked: {
            if(menuController.isVisible)
                menuController.close()
            else
                menuController.show()
        }
    }
}
