import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

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
            spacing: 20*Devices.density

            Item { height: 20*Devices.density; width: 10 }
            GroupBox {
                title: qsTr("Heights")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: Math.floor(width/(180*Devices.density))

                    Label { text: "statusBarHeight: <b>" + Math.floor(View.statusBarHeight*10)/10 + "</b>" }
                    Label { text: "navigationBarHeight: <b>" + Math.floor(View.navigationBarHeight*10)/10 + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Objects")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    Label { text: "root: <b>" + View.root + "</b>" }
                    Label { text: "window: <b>" + View.window + "</b>" }
                }
            }

            GroupBox {
                title: qsTr("Other")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    Label {
                        text: "layoutDirection: <b>" + layoutDirectionName + "</b>"
                        property string layoutDirectionName: {
                            switch(View.layoutDirection) {
                            case Qt.LeftToRight:
                                return "LeftToRight"
                            case Qt.RightToLeft:
                                return "RightToLeft"
                            }
                        }
                    }
                    Label { text: "offlineStoragePath: <b>" + View.offlineStoragePath + "</b>" }
                }
            }
            Item { height: 20*Devices.density; width: 10 }
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
        text: qsTr("View")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
