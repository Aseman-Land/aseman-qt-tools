import QtQuick 2.7
import QtQuick.Controls 2.0
import AsemanTools 1.0

Item {

    Settings {
        id: settings
        source: AsemanApp.homePath + "/settings.ini"
        category: "General"

        property int number: 10
        property string text: "test Text"
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("Settings")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }

    Label {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.margins: 10*Devices.density
        text: "Every changes in this page will be saved."
    }

    Column {
        anchors.centerIn: parent

        SpinBox {
            anchors.horizontalCenter: parent.horizontalCenter
            value: settings.number
            onValueChanged: settings.number = value
        }

        TextField {
            anchors.horizontalCenter: parent.horizontalCenter
            text: settings.text
            onTextChanged: settings.text = text
        }
    }
}
