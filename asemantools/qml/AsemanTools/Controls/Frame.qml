import QtQuick 2.0
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

Item {
    width: 200
    height: 150

    property color backgroundColor: masterPalette.window
    property alias shadowSize: shadow.opacity

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
            color: "#000000"
        }

        Item {
            id: fframe
            anchors.fill: parent

            Canvas {
                id: canvas
                anchors.fill: parent
                anchors.margins: -padding+1
                property real radius: 5
                property real padding: 5
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

