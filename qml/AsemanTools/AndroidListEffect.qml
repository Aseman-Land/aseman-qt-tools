import QtQuick 2.0
import AsemanTools 1.1

MouseEventListener {
    id: listenter
    clip: true

    property Flickable flickable

    property real minimumSensivityX: 10*Devices.density
    property real minimumSensivityY: 10*Devices.density

    property real ignoreDelayX: 0
    property real ignoreDelayY: 0

    property real topMargin: 0
    property real bottomMargin: 0

    onMouseYChanged: {
        if(!flickable)
            return
        prv.deltaY = mouseY-prv.lastMouseY
        if(prv.ignoreY)
            ignoreEvent()
        if(ignoreDelayY && Math.abs(prv.deltaY) > ignoreDelayY)
            prv.ignoreY = false

        if(!prv.lockX && (flickable.atYEnd || flickable.atYBeginning)) {
            if(Math.abs(prv.deltaY) > minimumSensivityY)
                prv.lockY = true
            if(prv.deltaY > minimumSensivityY)
                ignoreEvent()
        } else {
            prv.lastMouseY = mouseY
            prv.deltaY = 0
        }
    }
    onMouseXChanged: {
        if(!flickable)
            return
        prv.deltaX = mouseX-prv.lastMouseX
        if(prv.lockY)
            return
        if(prv.ignoreX)
            ignoreEvent()
        if(ignoreDelayX && Math.abs(prv.deltaX) > ignoreDelayX)
            prv.ignoreX = false
        if(Math.abs(prv.deltaX) > minimumSensivityX)
            prv.lockX = true
    }

    onMousePressed: {
        prv.lastMouseY = mouseY
        prv.lastMouseX = mouseX
        prv.ignoreX = (ignoreDelayX? true : false)
        prv.ignoreY = (ignoreDelayY? true : false)
    }
    onMouseReleased: {
        if(prv.deltaY>minimumSensivityY)
            ignoreEvent()
        prv.lockX = false
        prv.lockY = false
        prv.deltaY = 0
        prv.deltaX = 0
    }

    QtObject {
        id: prv

        property real deltaY
        property real deltaX
        property bool lockX
        property bool lockY
        property real lastMouseY
        property real lastMouseX
        property bool ignoreX
        property bool ignoreY

        Behavior on deltaY {
            NumberAnimation {easing.type: Easing.OutCubic; duration: 200}
        }
    }

    Rectangle {
        width: height
        color: "#aaaaaa"
        opacity: 0.2
        z: 10
        height: {
            var h = newHeight*2,
                w = listenter.width
            if(h < 4)
                return 0

            var sinb2 = h/Math.pow(w*w + h*h, 0.5)
            var c = 2*Math.asin(sinb2)
            var r = w/Math.sin(c)
            return 2*r
        }

        radius: width/2
        x: parent.width/4 + listenter.mouseX/2 - width/2
        y: prv.deltaY<0? listenter.height - newHeight - bottomMargin : newHeight - height + topMargin

        property real newHeight: Math.pow( Math.abs(prv.deltaY), 0.6 )
    }
}
