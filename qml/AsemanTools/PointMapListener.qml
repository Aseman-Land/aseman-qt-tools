import QtQuick 2.0
import AsemanTools 1.0

AsemanObject {
    property Item source
    property Item dest
    property real x: 0
    property real y: 0

    readonly property point result: {
        var prnt = source
        var rX=0, rY=0;
        while(prnt != dest) {
            if(!prnt) return Qt.point(-1, -1)
            rX += prnt.x
            rY += prnt.y
            prnt = prnt.parent
        }

        return Qt.point(rX+x, rY+y)
    }
}
