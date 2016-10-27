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
                title: qsTr("htmlWidth(string)")
                width: parent.width - 40*Devices.density
                anchors.horizontalCenter: parent.horizontalCenter

                ColumnLayout {
                    width: parent.width

                    TextArea {
                        id: htmlText
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: 200*Devices.density
                        placeholderText: "Write html code to calculate width"
                    }

                    Label { text: "The width is: " + TextTools.htmlWidth(htmlText.text) }
                }
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
        text: qsTr("TextTools")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
