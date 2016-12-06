import QtQuick 2.0
import AsemanTools 1.0

Item {
    height: 50*Devices.density

    property real minimumWidth: 120*Devices.density
    property alias model: tabBar.model
    property alias currentIndex: tabBar.currentIndex
    property alias layoutDirection: tabBar.layoutDirection
    property color highlightColor: "#03A9F4"
    property real fontSize: 12*Devices.fontDensity

    Rectangle { anchors.fill: tabBar }

    AsemanListView {
        id: tabBar
        anchors.fill: parent
        orientation: Qt.Horizontal
        layoutDirection: View.layoutDirection
        currentIndex: view.currentIndex
        onCurrentIndexChanged: view.currentIndex = currentIndex

        property real itemWidth: {
            var res = tabBar.width/tabBar.count
            if(res < minimumWidth)
                res = minimumWidth
            return res
        }

        delegate: Item {
            height: tabBar.height
            width: tabBar.itemWidth

            Text {
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
                maximumLineCount: 1
                elide: Text.ElideRight
                font.pixelSize: fontSize
                color: tabBar.currentIndex==index? highlightColor : "#333333"
                text: tabBar.model[index]
            }

            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }
        }
        highlightMoveDuration: 400
        highlight: Item {
            height: tabBar.height
            width: tabBar.itemWidth

            Rectangle {
                width: parent.width
                height: 3*Devices.density
                anchors.bottom: parent.bottom
                color: highlightColor
            }
        }
    }
}
