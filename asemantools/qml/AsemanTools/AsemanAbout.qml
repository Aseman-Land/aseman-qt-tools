/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import AsemanTools 1.0

Rectangle {
    id: aseman_splash

    Image {
        id: logo
        anchors.centerIn: parent
        width: 200*Devices.density
        height: 142*Devices.density
        sourceSize: Qt.size(width,height)
        source: "files/aseman-special.png"
        z: 10
    }

    Text {
        id: desc_txt
        anchors.top: logo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20*Devices.density
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        font.pixelSize: 9*Devices.fontDensity
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        z: 10
        text: qsTr("Aseman is a non-profit organization, exists to support and lead the free, open source and cross-platform projects and researches.")
    }

    Text {
        id: goal_txt
        anchors.top: desc_txt.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20*Devices.density
        anchors.rightMargin: 20*Devices.density
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        font.pixelSize: 9*Devices.fontDensity
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        z: 10
        text: qsTr("The Goal of the Aseman is to provide free and secure products to keep people’s freedom and their privacy.")
    }

    MouseArea {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 40*Devices.density
        width: 300*Devices.density
        z: 10
        cursorShape: Qt.PointingHandCursor
        onClicked: Qt.openUrlExternally("http://aseman.co")

        Text {
            anchors.centerIn: parent
            font.pixelSize: 9*Devices.fontDensity
            font.bold: true
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Home Page")
        }
    }

    Component {
        id: img_component
        Image {
            id: img
            width: parent.width
            height: parent.height
            source: "files/splash-back.jpg"
            fillMode: Image.PreserveAspectCrop
            opacity: 0
            scale: 1

            Behavior on opacity {
                NumberAnimation{ easing.type: Easing.Linear; duration: create_timer.first?0:create_timer.interval }
            }
            Behavior on scale {
                NumberAnimation{ easing.type: Easing.Linear; duration: kill_timer.interval }
            }

            Timer {
                id: kill_timer
                interval: create_timer.interval*2
                onTriggered: img.destroy()
            }

            Component.onCompleted: {
                opacity = 1
                scale = 3
                kill_timer.start()
                create_timer.first = false
            }
        }
    }

    Timer {
        id: create_timer
        repeat: true
        interval: 6000
        triggeredOnStart: true
        Component.onCompleted: start()
        onTriggered: img_component.createObject(aseman_splash)

        property bool first: true
    }
}
