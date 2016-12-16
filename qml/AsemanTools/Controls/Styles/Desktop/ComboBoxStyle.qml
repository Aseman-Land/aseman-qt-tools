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

import QtQuick 2.1
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0
import AsemanTools 1.0

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

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 4*Devices.density
            width: 12*Devices.density
            height: width
            sourceSize: Qt.size(width,height)
            source: "images/arrow-down.png"
        }
    }
}
