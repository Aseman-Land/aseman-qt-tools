QT += qml quick

android {
    manifest.source = android-build
    manifest.target = .
    COPYFOLDERS += manifest
    include(qmake/copyData.pri)
    copyData()

    QT += androidextras
    SOURCES += \
        asemantools/asemanjavalayer.cpp \
        asemantools/asemanandroidservice.cpp

    HEADERS += \
        asemantools/asemanjavalayer.h \
        asemantools/asemanandroidservice.h
} else {
    ios {

    } else {
        contains(BUILD_MODE,ubuntutouch) {
            DEFINES += Q_OS_UBUNTUTOUCH
        } else {
            QT += widgets

            HEADERS += \
                asemantools/asemanmimeapps.h \
                asemantools/qtsingleapplication/qtsinglecoreapplication.h \
                asemantools/qtsingleapplication/qtsingleapplication.h \
                asemantools/qtsingleapplication/qtlockedfile.h \
                asemantools/qtsingleapplication/qtlocalpeer.h

            SOURCES += \
                asemantools/asemanmimeapps.cpp \
                asemantools/qtsingleapplication/qtsinglecoreapplication.cpp \
                asemantools/qtsingleapplication/qtsingleapplication.cpp \
                asemantools/qtsingleapplication/qtlockedfile.cpp \
                asemantools/qtsingleapplication/qtlocalpeer.cpp

            win32: SOURCES += asemantools/qtsingleapplication/qtlockedfile_win.cpp
            unix:  SOURCES += asemantools/qtsingleapplication/qtlockedfile_unix.cpp
        }
    }
}

QML_IMPORT_PATH = \
    asemantools/qml/

contains(QT,sensors) {
    DEFINES += ASEMAN_SENSORS
    SOURCES += asemantools/asemansensors.cpp
    HEADERS += asemantools/asemansensors.h
}
linux {
contains(QT,dbus) {
    DEFINES += ASEMAN_NOTIFICATION
    SOURCES += asemantools/asemannotification.cpp
    HEADERS += asemantools/asemannotification.h
}
}

SOURCES += \
    asemantools/asemandevices.cpp \
    asemantools/asemanqtlogger.cpp \
    asemantools/asemantools.cpp \
    asemantools/asemandesktoptools.cpp \
    asemantools/asemanlistobject.cpp \
    asemantools/asemanhashobject.cpp \
    asemantools/asemanquickview.cpp \
    asemantools/asemanapplication.cpp \
    asemantools/asemancalendarconvertercore.cpp \
    asemantools/asemancalendarconverter.cpp \
    asemantools/asemanbackhandler.cpp \
    asemantools/asemansysteminfo.cpp \
    asemantools/asemanabstractcolorfulllistmodel.cpp \
    asemantools/asemanimagecoloranalizor.cpp \
    asemantools/asemancountriesmodel.cpp \
    asemantools/asemanmimedata.cpp \
    asemantools/asemandragobject.cpp \
    $$PWD/asemandownloader.cpp

HEADERS += \
    asemantools/asemandevices.h \
    asemantools/asemanqtlogger.h \
    asemantools/asemantools.h \
    asemantools/asemandesktoptools.h \
    asemantools/asemanlistobject.h \
    asemantools/asemanhashobject.h \
    asemantools/asemanquickview.h \
    asemantools/asemanapplication.h \
    asemantools/aseman_macros.h \
    asemantools/asemancalendarconvertercore.h \
    asemantools/asemancalendarconverter.h \
    asemantools/asemanbackhandler.h \
    asemantools/asemansysteminfo.h \
    asemantools/asemanabstractcolorfulllistmodel.h \
    asemantools/asemanimagecoloranalizor.h \
    asemantools/asemancountriesmodel.h \
    asemantools/asemanmimedata.h \
    asemantools/asemandragobject.h \
    $$PWD/asemandownloader.h

OTHER_FILES += \
    asemantools/android-build/src/land/aseman/android/AsemanActivity.java \
    asemantools/android-build/src/land/aseman/android/AsemanApplication.java \
    asemantools/android-build/src/land/aseman/android/AsemanJavaLayer.java \
    asemantools/android-build/src/land/aseman/android/AsemanService.java \
    asemantools/android-build/src/land/aseman/android/AsemanBootBroadcast.java \
    asemantools/android-build/src/land/aseman/android/AsemanServiceDelegate.java

RESOURCES += \
    asemantools/asemanresource.qrc
