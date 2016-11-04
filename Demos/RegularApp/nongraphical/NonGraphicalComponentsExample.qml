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
                text: "Downloader"
                onClicked: appendRequest(downloader_component)
            }
            MainMenuItem {
                text: "Encrypter"
                onClicked: appendRequest(encrypter_component)
            }
            MainMenuItem {
                text: "ImageColorAnalizor"
                onClicked: appendRequest(imageColorAnalizor_component)
            }
            MainMenuItem {
                text: "MapDownloader"
                onClicked: appendRequest(mapDownloader_component)
            }
            MainMenuItem {
                text: "NetworkSleepManager"
                onClicked: appendRequest(networkSleepManager_component)
            }
            MainMenuItem {
                text: "Notification"
                onClicked: appendRequest(notification_component)
            }
            MainMenuItem {
                text: "Settings"
                onClicked: appendRequest(settings_component)
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
        text: qsTr("Non-Graphical Components")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }

    Component {
        id: settings_component
        SettingsExample {
            anchors.fill: parent
        }
    }

    Component {
        id: downloader_component
        DownloaderExample {
            anchors.fill: parent
        }
    }

    Component {
        id: encrypter_component
        EncrypterExample {
            anchors.fill: parent
        }
    }

    Component {
        id: imageColorAnalizor_component
        ImageColorAnalizorExample {
            anchors.fill: parent
        }
    }

    Component {
        id: mapDownloader_component
        MapDownloaderExample {
            anchors.fill: parent
        }
    }

    Component {
        id: networkSleepManager_component
        NetworkSleepManagerExample {
            anchors.fill: parent
        }
    }

    Component {
        id: notification_component
        NotificationExample {
            anchors.fill: parent
        }
    }
}
