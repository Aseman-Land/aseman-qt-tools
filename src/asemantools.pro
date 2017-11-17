TEMPLATE = lib
TARGET = AsemanToolsQml
QT += qml quick gui
CONFIG += qt plugin
CONFIG -= android_install

isEmpty(ASEMAN_BUILD_DEST) {
    DESTDIR = qml/AsemanTools/AsemanTools
} else {
    DESTDIR = $$ASEMAN_BUILD_DEST/qml/AsemanTools
}

uri = AsemanTools
static {
    QMAKE_MOC_OPTIONS += -Muri=$$uri
    DEFINES += ASEMAN_STATIC_BUILD
}
ios {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

TARGET = $$qtLibraryTarget($$TARGET)

DEFINES += ASEMAN_QML_PLUGIN QT_MESSAGELOGCONTEXT
android|ios {
    DEFINES += DISABLE_KEYCHAIN
}

include(asemantools.pri)

SOURCES += \
    asemantoolsplugin.cpp

HEADERS += \
    asemantoolsplugin.h

QMLDIR_VALUE = $$cat(qmldir, blob) 'plugin AsemanToolsQml'
write_file($$OUT_PWD/$$DESTDIR/qmldir, QMLDIR_VALUE)

qmlFiles.source = AsemanTools/
qmlFiles.target = $$DESTDIR/../AsemanTools
COPYFOLDERS += qmlFiles

!win32-msvc* {
    include (qmake/copyData.pri)
    copyData ()
}

isEmpty(PREFIX) {
    PREFIX = $$[QT_INSTALL_QML]
}

installPath = $$PREFIX/$$replace(uri, \\., /)
qmldir.files = $$OUT_PWD/$$DESTDIR/qmldir $$OUT_PWD/$$DESTDIR/plugins.qmltypes
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
