/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0
import AsemanTools 1.0

ButtonStyle {
    SystemPalette {
        id: masterPalette
    }

    background: Item {
        implicitWidth: 80*Devices.density
        implicitHeight: 32*Devices.density

        Item {
            id: frame
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 3*Devices.density
                color: control.pressed? masterPalette.window : "#00000000"
                border.width: !control.pressed? 1 : 0
                border.color: !control.pressed? Qt.lighter(masterPalette.highlight, 1.2) : "#00000000"
                opacity: control.hovered? 0.7 : 0

                Behavior on opacity {
                    NumberAnimation{ easing.type: Easing.OutCubic; duration: 300 }
                }
            }
        }

        InnerShadow {
            anchors.fill: source
            source: frame
            radius: 3.0*Devices.density
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: control.pressed? 0.6 : 0
            color: "#000000"
        }
    }

    label: Item {
        Row {
            anchors.centerIn: parent

            Image {
                height: 22*Devices.density
                width: height
                source: control.iconSource
                sourceSize: Qt.size(width,height)
                visible: status == Image.Ready
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                color: masterPalette.windowText
                text: control.text
            }
        }
    }
}
