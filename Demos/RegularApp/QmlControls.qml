import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {

    ColumnLayout {
        anchors.centerIn: parent

        Switch {
            text: qsTr("Switch")
        }

        SpinBox {
        }

        Slider {
            value: 0.5
        }

        CheckBox {
            text: qsTr("Check Box")
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: qsTr("Press Me 1")
            }

            Button {
                text: qsTr("Press Me 2")
            }
        }
    }
}
