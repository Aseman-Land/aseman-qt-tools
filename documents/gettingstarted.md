
# Getting Started

## QML Module

To use AsemanQtTools in the module mode just import module in the qml files like below:
```
import AsemanTools 1.0
```
And use it.

<b>Note:</b> You can't use AsemanTools in the android and ios apps in the qml-module mode.

## Embeded mode

It's same as the QML Module mode. But you need to initialize module in the C++ ```main()``` function.

```C++
#include "asemantools/asemanqttools.h"
...
int main(int argc, char *argv[])
{
    AsemanQtTools::registerTypes("AsemanTools");
    ...
}

```

## Note

Some features of the AsemanTools needs ```AsemanMain``` component. So you should create it in the ```main.qml``` file.

## Android and iOS Note

To use AsemanTools in the Android and iOS applications, you should use Aseman initializers instead of the Qt initializers. Note that Aseman initializers inherits from the Qt initializers. 

So add below lines to the pro files:

```
ios {
    QTPLUGIN += qsqlite
    QMAKE_INFO_PLIST = $$PWD/asemantools/iOS/info.plist
}
android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/asemantools/android
}
```
You can also copy them, change above paths and change the files.
