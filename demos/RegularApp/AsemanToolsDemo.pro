TEMPLATE = app
DEFINES += DISABLE_KEYCHAIN

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

QT += qml quick
QT += widgets
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

include(deployment.pri)
include(../../asemantools.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat
