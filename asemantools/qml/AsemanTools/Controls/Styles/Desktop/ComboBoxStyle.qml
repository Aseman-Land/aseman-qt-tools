import QtQuick 2.2
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

ComboBoxStyle {
    property color backgroundColor: masterPalette.window
    property color textColor: masterPalette.windowText

    SystemPalette {
        id: masterPalette
    }

    background: Item {
        implicitWidth: 120
        implicitHeight: 32

        Item {
            id: frame
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
                color: Qt.darker(backgroundColor,1.1)
            }
        }

        InnerShadow {
            anchors.fill: source
            source: frame
            radius: 4.0
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: control.pressed? 0.5 : 0.2
            color: "#000000"
        }
    }
}
