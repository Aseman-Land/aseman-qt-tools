import QtQuick 2.0
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

RadioButtonStyle {
    property color backgroundColor: masterPalette.base

    SystemPalette {
        id: masterPalette
    }

    indicator: Item {
        implicitWidth: 24
        implicitHeight: 24

        Item {
            id: frame
            anchors.fill: parent
            anchors.margins: 1

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: width/2
                color: backgroundColor
            }
        }

        InnerShadow {
            anchors.fill: source
            source: frame
            radius: 4.0
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: control.pressed? 0.6 : 0.4
            color: "#000000"
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: 10
            radius: width/2
            color: masterPalette.text
            opacity: 0.8
            visible: control.checked
        }
    }

    label: Text {
        color: masterPalette.windowText
        text: control.text
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}

