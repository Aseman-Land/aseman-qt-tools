import QtQuick 2.7
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Item {

    MapDownloader {
        id: mapDownloader
        destination: Devices.localFilesPrePath + AsemanApp.tempPath
        mapProvider: mapProviderCombo.currentIndex
        size: Qt.size(img.width, img.height)
        zoom: 16
    }

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        ColumnLayout {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            ComboBox {
                id: mapProviderCombo
                Layout.fillWidth: true
                model: ["Google Map"]
            }

            TextArea {
                id: altTxt
                placeholderText: qsTr("Altitude")
                Layout.fillWidth: true
            }

            TextField {
                id: longTxt
                placeholderText: qsTr("Longitude")
                Layout.fillWidth: true
            }

            Button {
                text: "Download"
                Layout.fillWidth: true
                Material.foreground: Material.LightBlue
                onClicked: mapDownloader.download( Qt.point(altTxt.text, longTxt.text) )
            }
        }

        Image {
            id: img
            anchors.top: column.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20*Devices.density
            verticalAlignment: Image.AlignTop
            horizontalAlignment: Image.AlignHCenter
            fillMode: Image.PreserveAspectFit
            source: mapDownloader.image

            BusyIndicator {
                anchors.centerIn: parent
                width: 40*Devices.density
                height: width
                running: mapDownloader.downloading
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("MapDownloader")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
