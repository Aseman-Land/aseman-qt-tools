import QtQuick 2.7
import AsemanTools 1.0

AsemanApplication {
    id: app
    applicationName: "Regular App"
    applicationAbout: "It's an regular app"
    applicationDisplayName: "Regular App"
    applicationVersion: "1.0.0"
    applicationId: "5371c896-7f09-4013-a657-e6338fae82b0"
    organizationDomain: "co.aseman"
    organizationName: "Aseman Team"

    property variant appMain

    Component.onCompleted: { // Control app to run one instance
        if(app.isRunning) {
            console.debug("Another instance is running. Trying to make that visible...")
            Tools.jsDelayCall(1, function(){
                app.sendMessage("show")
                app.exit(0)
            })
        } else {
            var component = Qt.createComponent("AppWindow.qml", Component.Asynchronous);
            var callback = function(){
                if(component.status == Component.Ready)
                    appMain = component.createObject(app)
                else if(component.status == Component.Error) {
                    console.error(component.errorString())
                }
            }
            component.statusChanged.connect(callback)
            callback()
        }
    }
}
