/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    Kaqaz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Kaqaz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0

Item {
    id: checkbox
    width: 48*physicalPlatformScale
    height: 25*physicalPlatformScale
    smooth: true

    property color color: "#ffffff"
    property bool checked: false
    property alias cursorShape: marea.cursorShape

    property bool labels: true

    Rectangle {
        id: border
        anchors.fill: parent
        radius: height/2
        color: "#00000000"
        border.width: 1*physicalPlatformScale
        border.color: checkbox.color
    }

    Rectangle {
        id: bilbilak
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 2*physicalPlatformScale
        x: checkbox.checked? parent.width - width - 2*physicalPlatformScale : 2*physicalPlatformScale
        width: height
        radius: height/2
        color: checkbox.color

        Behavior on x {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 200 }
        }
    }

    Item {
        id: on_frame
        anchors.left: parent.left
        anchors.right: bilbilak.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 2*physicalPlatformScale
        clip: true
        visible: labels

        Text {
            id: on_txt
            anchors.centerIn: parent
            font.pixelSize: 10*fontsScale
            font.family: SApp.globalFontFamily
            color: checkbox.color
        }
    }

    Item {
        id: off_frame
        anchors.left: bilbilak.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 2*physicalPlatformScale
        clip: true
        visible: labels

        Text {
            id: off_txt
            anchors.centerIn: parent
            font.pixelSize: 10*fontsScale
            font.family: SApp.globalFontFamily
            color: checkbox.color
        }
    }

    MouseArea {
        id: marea
        anchors.fill: parent
        onClicked: checkbox.checked = !checkbox.checked
    }

    Connections{
        target: SApp
        onLanguageUpdated: initTranslations()
    }

    function initTranslations(){
        on_txt.text  = qsTr("On")
        off_txt.text = qsTr("Off")
    }

    Component.onCompleted: {
        initTranslations()
    }
}
