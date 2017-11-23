QT += qml quick gui
android|ios {
    DEFINES += DISABLE_KEYCHAIN
}

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/asemantoolsplugin.cpp

HEADERS += \
    $$PWD/asemantoolsplugin.h

contains(DEFINES,ASEMAN_EMBEDED_MODE) {
    RESOURCES += \
        $$PWD/asemanresource_qml.qrc
}

