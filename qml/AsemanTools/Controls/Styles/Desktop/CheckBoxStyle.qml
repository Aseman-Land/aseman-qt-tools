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

CheckBoxStyle {

    property color backgroundColor: masterPalette.base

    SystemPalette {
        id: masterPalette
    }

    indicator: Item {
        implicitWidth: 24*Devices.density
        implicitHeight: 24*Devices.density

        Item {
            id: frame
            anchors.fill: parent
            anchors.margins: 1

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1*Devices.density
                radius: 5*Devices.density
                color: backgroundColor
            }
        }

        InnerShadow {
            anchors.fill: source
            source: frame
            radius: 4.0*Devices.density
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1*Devices.density
            opacity: control.pressed? 0.6 : 0.4
            color: "#000000"
        }

        Image {
            anchors.fill: parent
            anchors.margins: 5*Devices.density
            source: "images/yes.png"
            sourceSize: Qt.size(width,height)
            fillMode: Image.PreserveAspectCrop
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
