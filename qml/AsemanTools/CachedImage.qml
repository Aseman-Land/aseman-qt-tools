import QtQuick 2.0
import AsemanTools 1.0
import QtGraphicalEffects 1.0

Item {

    property alias radius: mask.radius
    property alias source: queueItem.source
    property alias percent: queueItem.percent

    property alias fillMode: image.fillMode
    property alias asynchronous: image.asynchronous
    property alias cache: image.cache
    property alias horizontalAlignment: image.horizontalAlignment
    property alias mirror: image.mirror
    property alias paintedHeight: image.paintedHeight
    property alias paintedWidth: image.paintedWidth
    property alias progress: image.progress
    property alias smooth: image.smooth
    property alias sourceSize: image.sourceSize
    property alias status: image.status
    property alias verticalAlignment: image.verticalAlignment


    Rectangle {
        id: mask
        anchors.fill: parent
        visible: false
    }

    Image {
        id: image
        anchors.fill: parent
        source: queueItem.result
        visible: radius == 0
    }

    OpacityMask {
        anchors.fill: parent
        source: radius != 0? image : null
        maskSource: mask
        cached: true
        visible: radius != 0
    }

    FileDownloaderQueueItem {
        id: queueItem
        downloaderQueue: DownloaderQueue
        fileName: {
            if(source.length == 0)
                return ""
            return Tools.md5(source) + "." + Tools.fileSuffix(source)
        }
    }
}
