import QtQuick 2.0
import QtMultimedia 5.8
import AsemanTools 1.1
import AsemanTools.Awesome 1.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2

Item {
    id: videoPlayer

    property bool controlsVisibled: true
    property alias source: video.source
    readonly property bool playing: video.playbackState == MediaPlayer.PlayingState
    property color color: Devices.isAndroid? "#55000000" : "#55ffffff"
    property color background: "#000000"
    property bool blur: !Devices.isAndroid

    onPlayingChanged: {
        if(playing)
            timer.restart()
        else
            controlsVisibled = true
    }

    Rectangle {
        id: videoRect
        color: videoPlayer.background
        anchors.fill: parent

        Video {
            id: video
            anchors.fill: parent

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(controlsVisibled && playing)
                        controlsVisibled = false
                    else
                        controlsVisibled = true
                    if(playing)
                        timer.restart()
                }
            }

            Label {
                id: errorLabel
                anchors.fill: parent
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: "#ffffff"
                text: video.errorString
            }

            focus: true
            Keys.onSpacePressed: playing? videoPlayer.pause() : videoPlayer.play()
        }
    }

    Timer {
        id: timer
        interval: 2000
        repeat: false
        onTriggered: if(playing && !slider.pressed) controlsVisibled = false
    }

    FastBlur {
        id: blurFrame
        source: videoRect
        width: videoRect.width
        height: videoRect.height
        anchors.bottom: parent.bottom
        radius: videoPlayer.blur? 64 : 0
        visible: false
    }

    OpacityMask {
        anchors.fill: parent
        maskSource: controlsMask
        source: blurFrame
        visible: videoPlayer.blur
    }

    Item {
        id: controlsMask
        anchors.fill: videoRect
        visible: false

        Rectangle {
            width: parent.width
            height: topControls.height
            y: topControls.y
        }

        Rectangle {
            width: parent.width
            height: bottomControls.height
            y: bottomControls.y
        }
    }

    Item {
        id: controls
        anchors.fill: controlsMask

        property real ratio: controlsVisibled? 1 : 0

        Behavior on ratio {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
        }

        Rectangle {
            id: topControls
            width: parent.width
            height: topRow.height
            y: height*(controls.ratio-1)
            color: videoPlayer.color

            RowLayout {
                id: topRow
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter

                Button {
                    flat: true
                    text: "Done"
                    Material.theme: Material.Dark
                    onClicked: {
                        video.stop()
                        BackHandler.back()
                    }
                }

                Label {
                    color: "#ffffff"
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                    text: "Marina Kaye - Homeless (live)"
                }

                Button {
                    flat: true
                    text: playing? Awesome.fa_pause : Awesome.fa_play
                    font.family: Awesome.family
                    Material.theme: Material.Dark
                    onClicked: playing? pause() : play()
                }
            }
        }

        Rectangle {
            id: bottomControls
            width: parent.width
            height: bottomRow.height
            y: parent.height - height*controls.ratio
            color: videoPlayer.color

            RowLayout {
                id: bottomRow
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 20*Devices.density
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    color: "#ffffff"
                    text: {
                        var pos = slider.pressed? slider.value : video.position
                        var time = Math.floor(pos/1000)
                        var secs = time%60
                        var allMins = Math.floor(time/60)
                        var mins = allMins % 60
                        var hours = Math.floor(allMins/60)
                        if(secs < 10)
                            secs = "0" + secs
                        if(mins < 10)
                            mins = "0" + mins

                        if(hours > 0)
                            return hours + ":" + mins + ":" + secs
                        else
                            return mins + ":" + secs
                    }
                }

                Slider {
                    id: slider
                    from: 0
                    value: video.position
                    to: video.duration
                    onMoved: video.seek(value)
                    Material.accent: "#ffffff"
                    Layout.fillWidth: true
                }

                Label {
                    color: "#ffffff"
                    text: {
                        var time = Math.floor(video.duration/1000)
                        var secs = time%60
                        var allMins = Math.floor(time/60)
                        var mins = allMins % 60
                        var hours = Math.floor(allMins/60)
                        if(secs < 10)
                            secs = "0" + secs
                        if(mins < 10)
                            mins = "0" + mins

                        if(hours > 0)
                            return hours + ":" + mins + ":" + secs
                        else
                            return mins + ":" + secs
                    }
                }
            }
        }
    }

    function play() {
        video.play()
    }

    function pause() {
        timer.stop()
        video.pause()
    }
}
