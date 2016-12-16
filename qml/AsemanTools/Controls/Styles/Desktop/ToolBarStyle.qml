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

ToolBarStyle {

    padding {
        left: 4*Devices.density
        right: 4*Devices.density
        top: 4*Devices.density
        bottom: 4*Devices.density
    }

    background: Rectangle {
        color: Desktop.titleBarColor

        Rectangle {
            width: parent.width
            anchors.top: parent.bottom
            height: 3*Devices.density
            opacity: 0.3
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
        }
    }
}
