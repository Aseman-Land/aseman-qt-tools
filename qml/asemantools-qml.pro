TEMPLATE = lib
TARGET = asemantoolsqml
QT += qml quick gui
CONFIG -= android_install
DESTDIR = AsemanTools

uri = AsemanTools
static {
    QMAKE_MOC_OPTIONS += -Muri=$$uri
    DEFINES += ASEMAN_STATIC_BUILD
}
ios {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

TARGET = $$qtLibraryTarget($$TARGET)

DEFINES += QT_MESSAGELOGCONTEXT
android|ios {
    DEFINES += DISABLE_KEYCHAIN
}

LIBS += -L$$OUT_PWD/../lib -lasemantools
INCLUDEPATH += ../lib

SOURCES += \
    asemantoolsplugin.cpp

HEADERS += \
    asemantoolsplugin.h

contains(DEFINES,ASEMAN_STATIC_BUILD) {
    RESOURCES += \
        $$PWD/asemanresource-qml.qrc
}

QMLDIR_VALUE = $$cat(qmldir, blob) 'plugin asemantoolsqml'
write_file($$OUT_PWD/$$DESTDIR/qmldir, QMLDIR_VALUE)

isEmpty(PREFIX) {
    PREFIX = $$[QT_INSTALL_QML]
}

installPath = $$PREFIX/$$replace(uri, \\., /)
qmldir.files = $$OUT_PWD/$$DESTDIR/qmldir
qmldir.path = $$installPath
target = $$TARGET
target.path = $$installPath
INSTALLS += target qmldir

!contains(DEFINES,ASEMAN_STATIC_BUILD) {
    qmlFile.files = AsemanTools/
    qmlFile.path = $$PREFIX
    INSTALLS += qmlFile
}
android {
    javaFiles.files = $$PWD/android-build/src/ $$PWD/android-build/res/
    javaFiles.path = $$[QT_INSTALL_PREFIX]/src/android/java/
    INSTALLS += javaFiles
}
