import QtQuick 2.7
import AsemanTools 1.0
import QtQuick.Controls 2.0

Item {

    Item {
        id: listv
        width: parent.width
        anchors.top: header.bottom
        anchors.bottom: parent.bottom

        Column {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 20*Devices.density

            Repeater {
                model: 5
                CheckBox {
                    id: checkBox
                    text: "Check " + index
                    onCheckedChanged: {
                        if(checked)
                            BackHandler.pushHandler(checkBox, function(){checkBox.checked = false})
                        else
                            BackHandler.removeHandler(checkBox)
                    }
                }
            }
        }
    }

    Header {
        id: header
        width: parent.width
        color: masterPalette.highlight
        text: qsTr("BackHandler")
        shadow: true
    }

    HeaderMenuButton {
        ratio: 1
        buttonColor: "white"
        onClicked: AsemanApp.back()
    }
}
