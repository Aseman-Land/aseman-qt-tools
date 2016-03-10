import QtQuick 2.0

MouseArea {
    onPressed: mouse.accepted = false
    onWheel: wheel.accepted = false
}

