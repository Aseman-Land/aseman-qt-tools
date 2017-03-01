import QtQuick 2.0
import AsemanTools 1.0

Item {

    property alias source: queueItem.source
    property alias percent: queueItem.percent

    property alias fillMode: image.fillMode
    property alias asynchronous: image.asynchronous
    property alias sourceSize: image.sourceSize

    Image {
        id: image
        anchors.fill: parent
        source: queueItem.result
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
