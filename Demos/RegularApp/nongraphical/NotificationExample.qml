import QtQuick 2.7
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {

    Notification {
        id: notification
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

            TextField {
                id: titleTxt
                placeholderText: qsTr("Title")
                Layout.fillWidth: true
            }

            TextArea {
                id: body
                placeholderText: qsTr("Body text")
                Layout.fillWidth: true
                Layout.preferredHeight: 200*Devices.density
            }

            Button {
                text: "Send"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: notification.sendNotify(titleTxt.text, body.text, "")
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Notification")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
