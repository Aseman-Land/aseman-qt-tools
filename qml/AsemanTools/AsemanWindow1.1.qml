import QtQuick 2.0
import QtQuick.Controls 2.0
import AsemanTools 1.0

ApplicationWindow {
    id: appWin

    property bool backController: true
    property bool try_close: false
    property alias masterPalette: palette
    readonly property bool portrait: width<height

    signal closeRequest()

    onCloseRequest: if(backController) AsemanApp.back()

    SystemPalette {
        id: palette
    }

    Timer {
        id: timer_delayer
        interval: 300
        repeat: false
    }

    Connections {
        target: AsemanApp
        onBackRequest: {
            if(timer_delayer.running)
                return

            timer_delayer.start()
            var res = BackHandler.back()
            if( !res && !Devices.isDesktop )
                appWin.tryClose()
        }
    }

    function tryClose() {
        try_close = true
        close()
    }

    Component.onCompleted: {
        View.registerWindow(appWin)
        View.root = appWin
    }
}
