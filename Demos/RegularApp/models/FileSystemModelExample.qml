import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import "../global"

Rectangle {
    color: masterPalette.window
    clip: true

    Button {
        id: backBtn
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10*Devices.density
        text: qsTr("Parent Folder")
        onClicked: listv.model.folder = listv.model.parentFolder
    }

    AsemanListView {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: backBtn.top
        anchors.topMargin: 10*Devices.density
        clip: true
        model: FileSystemModel {
            folder: AsemanApp.startPath
        }

        delegate: MainMenuItem {
            width: listv.width
            text: model.fileName
            onClicked: {
                if(model.fileIsDir)
                    listv.model.folder = model.filePath
                else
                    Qt.openUrlExternally(model.fileUrl)
            }
        }
    }

    PhysicalScrollBar {
        anchors.right: listv.right
        anchors.top: listv.top
        height: listv.height
        width: 6*Devices.density
        color: masterPalette.highlight
        scrollArea: listv
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("FileSystemModel")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "#ffffff"
        onClicked: BackHandler.back()
    }
}
