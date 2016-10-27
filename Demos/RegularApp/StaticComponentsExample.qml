import QtQuick 2.0
import AsemanTools 1.0

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
                text: "AsemanApp"
                onClicked: appendRequest(asemanApp_component)
            }
            MainMenuItem {
                text: "BackHandler"
                onClicked: appendRequest(backHandler_component)
            }
            MainMenuItem {
                text: "Devices"
                onClicked: appendRequest(devices_component)
            }
            MainMenuItem {
                text: "Desktop"
                onClicked: appendRequest(desktop_component)
            }
            MainMenuItem {
                text: "TextTools"
                onClicked: appendRequest(textToolsComponent)
            }
            MainMenuItem {
                text: "Tools"
                onClicked: appendRequest(toolsComponent)
            }
            MainMenuItem {
                text: "Settings"
                onClicked: appendRequest(settings_component)
            }
            MainMenuItem {
                text: "View"
                onClicked: appendRequest(view_component)
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
        text: qsTr("Static Components")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    Component {
        id: asemanApp_component
        AsemanAppExample {
            anchors.fill: parent
        }
    }

    Component {
        id: backHandler_component
        BackHandlerExample {
            anchors.fill: parent
        }
    }

    Component {
        id: devices_component
        DevicesExample {
            anchors.fill: parent
        }
    }

    Component {
        id: desktop_component
        DesktopExample {
            anchors.fill: parent
        }
    }

    Component {
        id: textToolsComponent
        TextToolsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: toolsComponent
        ToolsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: settings_component
        SettingsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: view_component
        ViewExample {
            anchors.fill: parent
        }
    }
}
