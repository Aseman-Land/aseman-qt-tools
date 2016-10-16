import QtQuick 2.7
import QtQuick.Window 2.2
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

AsemanWindow {
    id: mainWin
    width: 480
    height: 640
    title: qsTr("Hello World")
    visible: true
    backController: true

    Material.accent: Material.LightBlue
    Material.theme: Material.Light

    SlidePageManager {
        id: pageManger
        anchors.fill: parent

        mainComponent: Item {
            anchors.fill: parent

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
                        text: "Side Menu"
                        onClicked: pageManger.append(sideMenu_component)
                    }
                    MainMenuItem {
                        text: "Menu Controller"
                        onClicked: pageManger.append(menuController_component)
                    }
                    MainMenuItem {
                        text: "Material Button"
                        onClicked: pageManger.append(materialButton_component)
                    }
                    MainMenuItem {
                        text: "Settings"
                        onClicked: pageManger.append(settings_component)
                    }
                    MainMenuItem {
                        text: "Switch Layout"
                        onClicked: View.layoutDirection = (View.layoutDirection==Qt.LeftToRight? Qt.RightToLeft : Qt.LeftToRight)
                    }
                    MainMenuItem {
                        text: "Show Panel"
                        onClicked: btmPanel.item = qmlcontrols_component.createObject(btmPanel)
                    }
                    MainMenuItem {
                        text: "Show Message"
                        onClicked: msgDialog.show(okCancelMsg_component)
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
                text: qsTr("SlidePageManager")
                shadow: true
            }
        }
    }

    BottomPanel {
        id: btmPanel
    }

    MessageDialog {
        id: msgDialog
        anchors.fill: parent
    }

    Component {
        id: menuController_component
        MenuControllerExample {
            anchors.fill: parent
        }
    }

    Component {
        id: sideMenu_component
        SideMenuExample {
            anchors.fill: parent
        }
    }

    Component {
        id: materialButton_component
        MaterialButtonExample {
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
        id: qmlcontrols_component
        Rectangle {
            height: mainWin.height/2
            width: mainWin.width
            NullMouseArea { anchors.fill: parent }
            QmlControls { anchors.fill: parent }
        }
    }

    Component {
        id: okCancelMsg_component
        MessageDialogOkCancelWarning {
            message: "It's a test message"
            onOk: { console.debug("Ok"); msgDialog.hide() }
            onCanceled: console.debug("Cancel")
        }
    }
}
