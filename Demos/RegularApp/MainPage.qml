import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import AsemanTools 1.0

Item {
    clip: true

    SwipeView {
        id: swipeView
        width: parent.width
        anchors.top: tabBar.bottom
        anchors.bottom: parent.bottom
        onCurrentIndexChanged: {
            BackHandler.removeHandler(swipeView)
            if(currentIndex > 0)
                BackHandler.pushHandler(swipeView, function(){currentIndex = 0})
        }

        QmlControls {}
        Item {}
    }

    TabBar {
        id: tabBar
        width: parent.width
        currentIndex: swipeView.currentIndex
        onCurrentIndexChanged: swipeView.currentIndex = currentIndex

        TabButton { text: qsTr("Home") }
        TabButton { text: qsTr("Page") }
    }
}
