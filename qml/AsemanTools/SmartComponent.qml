import QtQuick 2.0
import AsemanTools 1.0

SmartComponentCore {
    delayInterval: 1000

    function createLocalComponent() {
        return Qt.createComponent(source)
    }
}

