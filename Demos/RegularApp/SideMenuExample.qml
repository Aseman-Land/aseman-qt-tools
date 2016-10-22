import QtQuick 2.0
import AsemanTools 1.0

Rectangle {
    color: masterPalette.window

    MainPage {
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("SideMenu")
        shadow: true
    }

    SideMenu {
        id: sidebar
        anchors.fill: parent
        delegate: MouseArea {
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "#f0f0f0"
            }
        }
    }

    HeaderMenuButton {
        ratio: sidebar.percent
        buttonColor: Qt.rgba(1-ratio, 1-ratio, 1-ratio, 1)
        onClicked: {
            if(sidebar.showed)
                sidebar.discard()
            else
                sidebar.show()
        }
    }
}
