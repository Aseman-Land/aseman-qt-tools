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
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0

ProgressBarStyle {

    property color backgroundColor: Qt.darker(masterPalette.window, 1.2)
    property color highlightColor: masterPalette.highlight

    SystemPalette {
        id: masterPalette
    }

    background: Item {
        implicitWidth: 100
        implicitHeight: 30

        Item {
            id: frame
            anchors.fill: parent
            anchors.margins: 1

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
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
            opacity: control.pressed? 0.8 : 0.3
            color: "#000000"
        }
    }

    progress: Item {
        Item {
            id: pframe
            anchors.fill: parent
            anchors.margins: 1

            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
                color: highlightColor
            }

            RadialGradient {
                width: parent.width*0.9
                height: parent.height*0.8
                anchors.verticalCenter: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 0.6
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#ffffff" }
                    GradientStop { position: 0.5; color: "#00000000" }
                }
            }

            RadialGradient {
                width: parent.width*0.9
                height: parent.height*0.8
                anchors.verticalCenter: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 0.6
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#ffffff" }
                    GradientStop { position: 0.5; color: "#00000000" }
                }
            }
        }

        InnerShadow {
            anchors.fill: source
            source: pframe
            radius: 2.0
            samples: 16
            color: "#888888"
        }
    }
}
