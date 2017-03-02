import QtQuick 2.0
import AsemanTools 1.0
import QtGraphicalEffects 1.0

Item {

    property alias radius: mask.radius
    property alias source: queueItem.source
    property alias percent: queueItem.percent

    property alias fillMode: image.fillMode
    property alias asynchronous: image.asynchronous
    property alias sourceSize: image.sourceSize


    Rectangle {
        id: mask
        anchors.fill: parent
        visible: false
    }

    Image {
        id: image
        anchors.fill: parent
        source: queueItem.result
        visible: false
    }

    OpacityMask {
        anchors.fill: parent
        source: image
        maskSource: mask
        cached: true
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
