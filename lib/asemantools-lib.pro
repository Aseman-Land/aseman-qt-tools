TEMPLATE = lib
TARGET = asemantools
QT += qml quick gui
CONFIG -= android_install

win32: DESTDIR = $$OUT_PWD
ios {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

DEFINES += QT_MESSAGELOGCONTEXT LIBASEMANTOOLS_LIBRARY
android|ios {
    DEFINES += DISABLE_KEYCHAIN
}

include(asemantools.pri)

isEmpty(PREFIX) {
    isEmpty(INSTALL_HEADERS_PREFIX): INSTALL_HEADERS_PREFIX = $$[QT_INSTALL_HEADERS]
    isEmpty(INSTALL_LIBS_PREFIX): INSTALL_LIBS_PREFIX = $$[QT_INSTALL_LIBS]
} else {
    isEmpty(INSTALL_HEADERS_PREFIX): INSTALL_HEADERS_PREFIX = $$PREFIX/include
    isEmpty(INSTALL_LIBS_PREFIX): INSTALL_LIBS_PREFIX = $$PREFIX/lib/$$LIB_PATH
}

INSTALL_PREFIX = $$INSTALL_HEADERS_PREFIX/asemantools
INSTALL_HEADERS = $$HEADERS
include(qmake/headerinstall.pri)

target = $$TARGET
target.path = $$INSTALL_LIBS_PREFIX
INSTALLS += target

android {
    javaFiles.files = $$PWD/android-build/src/ $$PWD/android-build/res/
    javaFiles.path = $$[QT_INSTALL_PREFIX]/src/android/java/
    INSTALLS += javaFiles
}
