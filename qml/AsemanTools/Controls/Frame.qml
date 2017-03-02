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
import AsemanTools.Controls.Styles 1.0
import AsemanTools 1.0

Item {
    width: 200
    height: 150

    property color backgroundColor: masterPalette.window
    property alias shadowColor: shadow.color
    property alias shadowSize: shadow.opacity
    property alias radius: canvas.radius

    onBackgroundColorChanged: canvas.requestPaint()

    SystemPalette {
        id: masterPalette
    }

    Item {
        anchors.fill: parent
        z: 10
        clip: true

        DropShadow {
            id: shadow
            anchors.fill: source
            source: fframe
            radius: 4.0
            samples: 16
            horizontalOffset: 0
            verticalOffset: 1
            opacity: 0.4
            cached: true
            color: "#000000"
        }

        Item {
            id: fframe
            anchors.fill: parent

            Canvas {
                id: canvas
                anchors.fill: parent
                anchors.margins: -padding+1
                property real radius: 5*Devices.density
                property real padding: 5*Devices.density
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.save();

                    ctx.fillStyle = backgroundColor
                    ctx.beginPath();

                    ctx.moveTo(padding, height/2)
                    ctx.arc(radius+padding, radius+padding, radius, -Math.PI, -Math.PI/2, false )
                    ctx.arc(width-radius-padding, radius+padding, radius, -Math.PI/2, 0, false )
                    ctx.arc(width-radius-padding, height-radius-padding, radius, 0, Math.PI/2, false )
                    ctx.arc(radius+padding, height-radius-padding, radius, Math.PI/2, -Math.PI, false )
                    ctx.lineTo(padding, height/2)
                    ctx.lineTo(0, height/2)
                    ctx.lineTo(0, height)
                    ctx.lineTo(width, height)
                    ctx.lineTo(width, 0)
                    ctx.lineTo(0, 0)
                    ctx.lineTo(0, height/2)

                    ctx.fill()
                }
            }
        }
    }
}
