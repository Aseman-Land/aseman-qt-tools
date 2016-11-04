import QtQuick 2.0
import AsemanTools 1.0
import "../global"

Rectangle {
    id: scItem
    color: masterPalette.window

    signal appendRequest(variant component)

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
                text: "CountriesModel"
                onClicked: appendRequest(countriesModel_component)
            }

            MainMenuItem {
                text: "FileSystemModel"
                onClicked: appendRequest(fileSystemModel_component)
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
        text: qsTr("Model Components")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    Component {
        id: countriesModel_component
        CountriesModelExample {
            anchors.fill: parent
        }
    }

    Component {
        id: fileSystemModel_component
        FileSystemModelExample {
            anchors.fill: parent
        }
    }
}
