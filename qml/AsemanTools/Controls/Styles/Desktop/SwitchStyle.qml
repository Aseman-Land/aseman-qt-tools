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

SwitchStyle {

    property color backgroundColor: masterPalette.window
    property color handlerOnColor: masterPalette.highlight
    property color handlerOffColor: "#888888"

    SystemPalette {
        id: masterPalette
    }

    groove: Item {
        implicitWidth: 40
        implicitHeight: 24

        Item {
            id: frame
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
                color: Qt.darker(backgroundColor,1.1)
            }

            Image {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 6
                sourceSize: Qt.size(width, height)
                width: height
                source: "images/no.png"
                opacity: 0.5
            }

            Image {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 6
                sourceSize: Qt.size(width, height)
                width: height
                source: "images/yes.png"
                opacity: 0.5
            }
        }

        InnerShadow {
            anchors.fill: source
            source: frame
            radius: 4.0
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: 0.4
            color: "#000000"
        }
    }

    handle: Item {
        implicitWidth: 24
        implicitHeight: 24

        Item {
            id: hframe
            anchors.fill: parent
            anchors.margins: 2

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
                color: control.checked? handlerOnColor : handlerOffColor
            }

            Image {
                anchors.fill: parent
                anchors.margins: 4
                sourceSize: Qt.size(width, height)
                width: height
                source: control.checked? "images/yes_light.png" : "images/no_light.png"
            }
        }

        InnerShadow {
            anchors.fill: source
            source: hframe
            radius: 4.0
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: 0.3
            color: "#000000"
        }
    }
}
