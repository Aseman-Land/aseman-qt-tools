import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Controls 2.0 as QtControls
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2
import QtQuick.Controls.Private 1.0

Item {
    id: tcarea
    anchors.fill: textItem

    property color color: "#00BCD4"
    property Item textItem
    property Item cursorParent: Window.contentItem

    readonly property bool selected: textItem && textItem.selectionStart != textItem.selectionEnd
    property alias menuMore: menuRect.more

    property variant menuMap: [
        {"name": (selected? qsTr("Copy") : qsTr("Paste")), "action": function() {
            if(selected)
                textItem.copy()
            else
                textItem.paste()
            hideMenu()
        }},
        {"name": (selected? qsTr("More") : qsTr("Select All")), "action": function() {
            if(selected)
                menuMore = true
            else {
                textItem.selectAll()
                menuRect.showCursor()
            }
        }}
    ]
    property variant menuMoreMap: [
        {"name": qsTr("Cut"), "action": function() { textItem.cut(); hideMenu() }},
        {"name": (selected? qsTr("Paste") : qsTr("Copy")), "action": function() {
            if(selected)
                textItem.paste()
            else
                textItem.copy()
            hideMenu()
        }},
        {"name": qsTr("Select All"), "action": function() { textItem.selectAll(); menuRect.showCursor() }},
        {"name": qsTr("Back"), "action": function() { menuMore = false }}
    ]

    onCursorParentChanged: if(menuRect.visible) menuRect.showCursor()

    QtObject {
        id: prv
        property Item cursor0
        property Item cursor1
        property bool forceHidden: true
        property string itemText: textItem? textItem.text : ""

        onItemTextChanged: forceHidden = true
        onForceHiddenChanged: if(forceHidden) menuRect.visible = false

        function switchCursors() {
            var tmp = cursor0.propertyName
            cursor0.propertyName = cursor1.propertyName
            cursor1.propertyName = tmp
        }
    }

    PointMapListener { id: mapListener; source: tcarea; dest: cursorParent }

    Item {
        id: menuRect
        x: mapListener.result.x + extraX
        y: mapListener.result.y + extraY
        width: menuBack.width + 10*Devices.density
        height: menuBack.height + 10*Devices.density
        visible: false
        parent: cursorParent
        clip: true
        z: 1000002

        property real extraX
        property real extraY

        onVisibleChanged: {
            if(!visible) more = false
            if(visible)
                BackHandler.pushHandler(menuRect, function(){ menuRect.visible = false; textItem.deselect() } )
            else
                BackHandler.removeHandler(menuRect)
        }

        property bool more: false
        onMoreChanged: {
            if(more)
                BackHandler.pushHandler(menuItem, function(){ menuRect.more = false } )
            else
                BackHandler.removeHandler(menuItem)
        }

        DropShadow {
            anchors.fill: menuItem
            horizontalOffset: 0
            verticalOffset: 1*Devices.density
            radius: 8*Devices.density
            samples: 16
            color: "#80000000"
            source: menuItem
        }

        Item {
            id: menuItem
            anchors.fill: parent

            Rectangle {
                id: menuBack
                anchors.centerIn: parent
                width: menuRect.more? menuColumn.width : menuRow.width
                height: menuRect.more? menuColumn.height : menuRow.height
                color: "#ffffff"

                Behavior on width {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                }
                Behavior on height {
                    NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                }

                NullMouseArea { anchors.fill: parent }
            }

            Column {
                id: menuColumn
                visible: menuRect.more
                x: 5*Devices.density
                y: x

                Repeater {
                    model: menuMoreMap
                    delegate: QtControls.Button {
                        text: data.name
                        flat: true
                        onClicked: data.action()

                        property variant data: menuMoreMap[index]
                    }
                }
            }

            Row {
                id: menuRow
                visible: !menuRect.more
                x: 5*Devices.density
                y: x

                Repeater {
                    model: menuMap
                    delegate: QtControls.Button {
                        text: data.name
                        flat: true
                        onClicked: data.action()

                        property variant data: menuMap[index]
                    }
                }
            }
        }

        function showCursor() {
            var cItem = cursorParent
            var minX = cItem.width
            var maxX = 0
            var minY = cItem.height
            var maxY = 0
            for(var i=textItem.selectionStart; i<=textItem.selectionEnd; i++) {
                var rect = textItem.positionToRectangle(i)
                if(rect.x < minX)
                    minX = rect.x
                if(rect.x + rect.width > maxX)
                    maxX = rect.x + rect.width
                if(rect.y < minY)
                    minY = rect.y
                if(rect.y + rect.height > maxY)
                    maxY = rect.y + rect.height
            }

            var pnt = tcarea.mapToItem(cItem, 0, 0)
            minX += pnt.x
            maxX += pnt.x
            minY += pnt.y
            maxY += pnt.y

            var mrX = (maxX+minX)/2 - menuRect.width/2
            if(mrX < 0)
                mrX = 0
            if(mrX + menuRect.width > cItem.width)
                mrX = cItem.width - menuRect.width

            var mrY = minY - menuRect.height + 5*Devices.density
            if(mrY < 0)
                mrY = maxY + 30*Devices.density
            if(mrY + menuRect.height > cItem.height)
                mrY = cItem.height/2 - height/2

            extraX = mrX - pnt.x
            extraY = mrY - pnt.y

            menuRect.visible = true
            menuRect.more = false
        }
    }

    MouseArea {
        anchors.fill: parent
        onPressAndHold: {
            prv.forceHidden = false
            menuRect.visible = false
            textItem.cursorVisible = false
            textItem.focus = false
            var pos = textItem.positionAt(mouseX, mouseY)
            textItem.cursorPosition = pos
            textItem.selectWord()
            menuRect.showCursor()
        }
        onClicked: {
            prv.forceHidden = false
            var pos = textItem.positionAt(mouseX, mouseY)
            if(textItem.selectionStart != textItem.selectionEnd &&
               textItem.selectionStart < pos &&
               textItem.selectionEnd > pos && !menuRect.visible) {
                menuRect.showCursor()
            } else {
                textItem.deselect()
                textItem.cursorPosition = pos
                textItem.cursorVisible = true
                textItem.focus = true
                textItem.forceActiveFocus()
                menuRect.visible = false
                Devices.showKeyboard()
            }
        }
    }

    Item {
        id: cursorsScene
        width: tcarea.width
        height: tcarea.height
        parent: cursorParent
        x: mapListener.result.x
        y: mapListener.result.y
        z: 1000001
        visible: textItem && textItem.visible
    }

    Component {
        id: cursorComponent
        Item {
            id: cursorHandle
            width: 24*Devices.density
            height: width
            x: customPoint.x? customPoint.x : pnt.x - width/2
            y: customPoint.y? customPoint.y : pnt.y
            visible: {
                if(prv.forceHidden)
                    return false
                if(textItem.text.length == 0)
                    return false
                if(textItem && textItem.selectionStart != textItem.selectionEnd)
                    return true
                if(propertyName == "selectionStart")
                    return true
                return false
            }

            Behavior on x {
                NumberAnimation { easing.type: Easing.OutCubic; duration: customPoint.x? 0 : 300 }
            }
            Behavior on y {
                NumberAnimation { easing.type: Easing.OutCubic; duration: customPoint.y? 0 : 300 }
            }

            property string propertyName: "selectionStart"

            property point pnt: {
                if(!textItem || !textItem[propertyName])
                    return Qt.point(-1, -1)
                if(textItem.selectionStart == textItem.selectionEnd && propertyName == "selectionEnd")
                    return Qt.point(-1, -1)

                var point = textItem.positionToRectangle(textItem[propertyName])
                return Qt.point(point.x + point.width/2, point.y + point.height)
            }
            property point customPoint: Qt.point(0, 0)

            Canvas {
                  id: mycanvas
                  anchors.fill: parent
                  rotation: {
                      var reverse = (textItem && textItem.horizontalAlignment==TextEdit.AlignRight? -1 : 1)
                      if(textItem && textItem.selectionStart == textItem.selectionEnd)
                          return 0
                      else
                      if(propertyName == "selectionStart")
                          return 45*reverse
                      else
                          return -45*reverse
                  }
                  transformOrigin: Item.Top

                  property color fillColor: tcarea.color
                  onFillColorChanged: requestPaint()

                  onPaint: {
                      var ctx = getContext("2d");
                      ctx.fillStyle = fillColor
                      ctx.moveTo(width/2, 0)
                      ctx.lineTo(width, height/2)
                      ctx.bezierCurveTo(width, height/2, width, height, width/2, height)
                      ctx.bezierCurveTo(width/2, height, 0, height, 0, height/2)
                      ctx.lineTo(width/2, 0)
                      ctx.fill()
                  }

                  Behavior on rotation {
                      NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
                  }
              }

            MouseArea {
                anchors.fill: parent
                anchors.leftMargin: -10*Devices.density
                anchors.rightMargin: -10*Devices.density
                anchors.bottomMargin: -30*Devices.density
                onPositionChanged: {
                    var deltaX = mouseX-pinX
                    var deltaY = mouseY-pinY

                    customPoint.x = cursorHandle.x + deltaX
                    customPoint.y = cursorHandle.y + deltaY

                    var pos = textItem.positionAt(cursorHandle.x + cursorHandle.width/2, cursorHandle.y)
                    if(textItem.selectionStart == textItem.selectionEnd && propertyName == "selectionStart") {
                        textItem.cursorPosition = pos
                    } else if(propertyName == "selectionStart") {
                        if(pos < textItem.selectionEnd)
                            textItem.select(pos, textItem.selectionEnd)
                        else {
                            prv.switchCursors()
                            var rcvr = textItem.selectionEnd
                            if(rcvr == pos)
                                pos++
                            textItem.select(rcvr, pos)
                        }
                    } else {
                        if(pos > textItem.selectionStart)
                            textItem.select(textItem.selectionStart, pos)
                        else {
                            prv.switchCursors()
                            var rcvr = textItem.selectionStart
                            if(rcvr == pos)
                                pos--
                            textItem.select(pos, rcvr)
                        }
                    }
                }
                onPressed: {
                    pinPos = textItem[propertyName]
                    menuRect.visible = false
                    pinX = width/2
                    pinY = height
                }
                onReleased: {
                    customPoint = Qt.point(0, 0)
                    menuRect.showCursor()
                }

                property real pinX
                property real pinY
                property int pinPos
            }
        }
    }

    function hideMenu() {
        menuRect.visible = false
    }

    Component.onCompleted: {
        prv.cursor0 = cursorComponent.createObject(cursorsScene, {"propertyName": "selectionStart"})
        prv.cursor1 = cursorComponent.createObject(cursorsScene, {"propertyName": "selectionEnd"})
    }
}
