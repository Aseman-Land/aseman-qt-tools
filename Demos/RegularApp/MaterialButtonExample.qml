import QtQuick 2.7
import AsemanTools 1.0
import QtQuick.Controls 2.0

Item {

    AsemanListView {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        model: 20
        delegate: Item {
            width: listv.width
            height: 50*Devices.density

            Label {
                x: 20*Devices.density
                text: "Item " + model.index
                font.pixelSize: 10*Devices.fontDensity
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    NormalWheelScroll {
        flick: listv
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
        text: qsTr("MaterialDesignButton")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }

    MaterialDesignButton {
        anchors.fill: listv
        flickable: listv
        color: masterPalette.highlight
        list: [
            {"name": "Item 1", "icon": "", "method": function(){console.debug("Item 1 Clicked")}},
            {"name": "Item 2", "icon": "", "method": function(){console.debug("Item 2 Clicked")}},
            {"name": "Item 3", "icon": "", "method": function(){console.debug("Item 3 Clicked")}}
        ]
    }
}
