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

            Item { height: 20*Devices.density; width: 10 }
            GroupBox {
                title: qsTr("Methods")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    RowLayout {
                        Button { text: "Open File"; onClicked: resultLabel.text = Desktop.getOpenFileName() }
                        Button { text: "Open Files"; onClicked: resultLabel.text = Desktop.getOpenFileNames().join("\n") }
                    }
                    RowLayout {
                        Button { text: "Save File"; onClicked: resultLabel.text = Desktop.getSaveFileName() }
                        Button { text: "Get Directory"; onClicked: resultLabel.text = Desktop.getExistingDirectory() }
                    }
                    RowLayout {
                        Button { text: "Get Font"; onClicked: resultLabel.text = Desktop.getFont() }
                        Button { text: "Get Color"; onClicked: resultLabel.text = Desktop.getColor() }
                    }
                    RowLayout {
                        Button { text: "Get Text"; onClicked: resultLabel.text = Desktop.getText(View.window, "Title", "Enter the text") }
                        Button { text: "Show Menu"; onClicked: resultLabel.text = Desktop.showMenu(["Zero", "One", "", "Three"]) }
                    }
                    RowLayout {
                        Button { text: "YES or NO"; onClicked: resultLabel.text = Desktop.yesOrNo(View.window, "Title", "Just yes or no?") }
                        Button { text: "Show Message"; onClicked: Desktop.showMessage(View.window, "Title", "It's the message") }
                    }
                }
            }

            Item { height: 20*Devices.density; width: 10 }
            Label {
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Result:"
                font.bold: true
            }

            Label {
                id: resultLabel
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Item { height: 20*Devices.density; width: 10 }

            GroupBox {
                title: qsTr("Properties")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter
                clip: true

                GridLayout {
                    width: parent.width
                    columns: 1

                    RowLayout {
                        Button { text: "Show Tooltip"; onClicked: Desktop.tooltip = "Just a test tooltip" }
                    }

                    Label {
                        text: "Desktop Session: <b>" + desktopName + "</b>"
                        property string desktopName: {
                            switch(Desktop.desktopSession) {
                            case Desktop.Gnome:
                                return "Unknown"
                            case Desktop.GnomeFallBack:
                                return "GnomeFallBack"
                            case Desktop.Unity:
                                return "Unity"
                            case Desktop.Kde:
                                return "Kde"
                            case Desktop.Plasma:
                                return "Plasma"
                            case Desktop.Windows:
                                return "Windows"
                            case Desktop.Mac:
                                return "Mac"
                            default:
                            case Desktop.Unknown:
                                return "Unknown"
                            }
                        }
                    }
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
        text: qsTr("Desktop")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
