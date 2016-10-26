import QtQuick 2.7
import QtQuick.Window 2.2
import AsemanTools 1.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.2

AsemanWindow {
    id: mainWin
    width: 480
    height: 640
    title: qsTr("Hello World")
    visible: true
    backController: true

    Material.accent: Material.LightBlue
    Material.theme: Material.Light

    Rectangle {
        anchors.fill: parent
        color: "#000000"
    }

    SlidePageManager {
        id: pageManger
        anchors.fill: parent
        direction: (mainItem && mainItem.pageManagerDirection? Qt.Vertical : Qt.Horizontal)

        mainComponent: Rectangle {
            anchors.fill: parent

            property alias pageManagerDirection: pManagerSwitch.checked

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
                        text: "Back Handler"
                        onClicked: pageManger.append(backHandler_component)
                    }
                    MainMenuItem {
                        text: "Settings"
                        onClicked: pageManger.append(settings_component)
                    }
                    MainMenuItem {
                        text: "Vertical page manager"
                        onClicked: pManagerSwitch.checked = !pManagerSwitch.checked
                        Switch {
                            id: pManagerSwitch
                            anchors.verticalCenter: parent.verticalCenter
                            x: View.layoutDirection==Qt.LeftToRight? parent.width - width : 0
                        }
                    }
                    MainMenuItem {
                        text: "Right To Left"
                        onClicked: layoutSwitch.checked = !layoutSwitch.checked
                        Switch {
                            id: layoutSwitch
                            anchors.verticalCenter: parent.verticalCenter
                            x: View.layoutDirection==Qt.LeftToRight? parent.width - width : 0
                            onCheckedChanged: View.layoutDirection = (checked? Qt.RightToLeft : Qt.LeftToRight)
                        }
                    }
                    MainMenuItem {
                        text: "Show Panel"
                        onClicked: btmPanel.item = qmlcontrols_component.createObject(btmPanel)
                    }
                    MainMenuItem {
                        text: "Show Popup"
                        onClicked: msgDialog.visible = true
                    }
                    MainMenuItem {
                        text: "AsemanQtTools Github"
                        onClicked: Qt.openUrlExternally("https://github.com/Aseman-Land/aseman-qt-tools")
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

    Popup {
        id: msgDialog
        x: (mainWin.width - width) / 2
        y: (mainWin.height - height) / 2
        width: Math.min(mainWin.width, mainWin.height) / 3 * 2
        height: settingsColumn.implicitHeight + topPadding + bottomPadding
        modal: true
        focus: true

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20
            z: 100

            Label {
                text: "Message"
                font.bold: true
            }

            Label {
                text: "It's just a test message :)"
            }

            RowLayout {
                spacing: 10

                Button {
                    id: okButton
                    text: "Ok"
                    onClicked: msgDialog.close()

                    Material.foreground: Material.LightBlue
                    Material.background: "transparent"
                    Material.elevation: 0

                    Layout.preferredWidth: 0
                    Layout.fillWidth: true
                }
            }
        }
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
        id: backHandler_component
        BackHandlerExample {
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
}
