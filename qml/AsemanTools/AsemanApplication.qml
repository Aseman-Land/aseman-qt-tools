import QtQuick 2.0
import AsemanTools 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

AsemanApplicationBase {
    property url source
    readonly property alias appMain: prv.appMain

    AsemanObject {
        id: prv
        property Window appMain
    }

    onSourceChanged: {
        if(prv.appMain)
            prv.appMain.destroy()

        if(source.length == 0)
            return

        var component = Qt.createComponent(source, Component.Asynchronous);
        var callback = function(){
            if(component.status == Component.Ready)
                prv.appMain = component.createObject(app)
            else if(component.status == Component.Error) {
                console.error(component.errorString())

                var er = errorComponent.createObject(app)
                er.showError(component.errorString())
            }
        }
        component.statusChanged.connect(callback)
        callback()
    }


    Component {
        id: errorComponent
        ApplicationWindow {
            visible: true

            Rectangle {
                anchors.fill: parent
                color: "#000000"
            }

            MessageDialog {
                id: errorDialog
                title: "Fatal Error"
                text: "Application could not be started. Additional information:"
                onAccepted: app.exit(1)
            }

            function showError(text) {
                errorDialog.informativeText = text
                errorDialog.setVisible(true)
            }
        }
    }
}
