import QtQuick 2.0
import AsemanTools 1.0

AsemanObject {
    id: backAction
    property bool active: false
    onActiveChanged: {
        if(active)
            BackHandler.pushHandler(backAction, function(){ active = false })
        else
            BackHandler.removeHandler(backAction)
    }
}
