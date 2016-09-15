TEMPLATE = lib
TARGET = AsemanToolsQml
QT += qml quick widgets
CONFIG += qt plugin
DESTDIR = qml/AsemanTools/AsemanTools
#VERSION = 1.0.0

TARGET = $$qtLibraryTarget($$TARGET)
uri = AsemanTools

DEFINES += ASEMAN_QML_PLUGIN QT_MESSAGELOGCONTEXT

include(asemantools.pri)

SOURCES += \
    asemantoolsplugin.cpp

HEADERS += \
    asemantoolsplugin.h

qmlFiles.source = qml/AsemanTools/
qmlFiles.target = .
COPYFOLDERS += qmlFiles

include(qmake/qmlplugindump.pri)
!win32-msvc* {
    include (qmake/copyData.pri)
    copyData ()
}

isEmpty(PREFIX) {
    PREFIX = $$[QT_INSTALL_QML]
}

installPath = $$PREFIX/$$replace(uri, \\., /)
qmldir.files = $$OUT_PWD/qmldir $$OUT_PWD/$$DESTDIR/plugins.qmltypes
qmldir.path = $$installPath
qmlFile.files = qml/AsemanTools/
qmlFile.path = $$PREFIX
target = $$TARGET
target.path = $$installPath
INSTALLS += qmlFile qmldir target
