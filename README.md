# AsemanQtTools

AsemanQtTools, is the shared tools and functions, we used in the aseman's projects. It helps us to keep our projects update and stable on all platforms.

## [Developer Documents](documents/index.md)

## How to Setup/Build

### QML Module

To build AsemanQtTools as QML module, just simply run below commands:

```
mkdir build && cd build
qmake QT+=widgets QT+=multimedia QT+=dbus QT+=sensors QT+=positioning ../asemantools.pro
make
sudo make install
```

You can remove any of the QT configs if you don't need it.

### Embeded mode

To build it as Embeded mode, you should use asemantools.pri instead of the asemantools.pro.
so copy asemantools folder to the project directory and add below lines to your project's .pro file:

```
QT += widgets multimedia dbus sensors positioning
include(asemantools/asemantools.pri)

```

You can remove any of the QT configs if you don't need it.

