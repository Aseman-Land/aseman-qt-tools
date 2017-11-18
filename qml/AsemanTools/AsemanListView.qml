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

import QtQuick 2.3
import AsemanTools 1.0

ListView {
    id: listv

    maximumFlickVelocity: View.flickVelocity
    boundsBehavior: Devices.isIOS? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds

    readonly property real tabBarRatio: prv.tabBarExtra/tabBarHeight
    property real tabBarHeight: 50*Devices.density

    onTabBarHeightChanged: prv.tabBarExtra = tabBarHeight
    onContentYChanged: prv.optimizeTabBar()
    onContentHeightChanged: if(contentHeight<height) anim.start()

    NumberAnimation {
        id: anim
        target: prv
        property: "tabBarExtra"
        from: prv.tabBarExtra
        to: tabBarHeight
        easing.type: Easing.OutCubic
        duration: 250
    }

    Transition {
        id: android_transition
        NumberAnimation {
            properties: "x,y"
            duration: 0
        }
    }

    QtObject {
        id: prv

        property real lastContentY: listv.contentY+1
        property real tabBarExtra: listv.tabBarHeight

        function optimizeTabBar() {
            var minFlick = -tabBarHeight
            var maxFlick = listv.contentHeight - listv.height + minFlick
            if(listv.contentY > maxFlick || listv.contentY<0)
                return

            var newExtra = tabBarExtra - (listv.contentY-prv.lastContentY)
            if(newExtra<0)
                newExtra = 0
            if(listv.contentY < minFlick)
                newExtra = -listv.contentY
            else
            if(newExtra>tabBarHeight)
                newExtra = tabBarHeight

            tabBarExtra = newExtra
            prv.lastContentY = listv.contentY
        }
    }

    Component.onCompleted: if(!Devices.isIOS) rebound = android_transition
}
