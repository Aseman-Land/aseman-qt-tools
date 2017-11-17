/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANQTTOOLS_H
#define ASEMANQTTOOLS_H

#include <QtGlobal>
#include <QString>

class QObject;
class QQmlEngine;
class QJSEngine;
class AsemanQtTools
{
public:
#ifdef ASEMAN_STATIC_BUILD
    static bool registerTypes();
#endif
    static void registerTypes(const char *uri, bool exportMode = false);
    static void registerSecureTypes(const char *uri, bool exportMode = false);
    static bool safeRegisterTypes(const char *uri, QQmlEngine *engine);
    static void initializeEngine(QQmlEngine *engine, const char *uri);

    template<typename T>
    static int registerType(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode);

    template<typename T>
    static int registerModel(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode);

    template <typename T>
    static int registerSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName,
                                 QObject *(*callback)(QQmlEngine *, QJSEngine *), bool exportMode);

    template<typename T>
    static int registerUncreatableType(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString& reason, bool exportMode);

    static class AsemanQuickViewWrapper *quickView(QQmlEngine *engine);
    static class AsemanApplication *application();
    static class AsemanDesktopTools *desktopTools();
    static class AsemanDevices *devices();
    static class AsemanQtLogger *qtLogger();
#ifdef Q_OS_ANDROID
    static class AsemanJavaLayer *javaLayer();
#endif
    static class AsemanTools *tools();
    static class AsemanSystemInfo *systemInfo();
    static class AsemanFileDownloaderQueue *getDownloaderQueue(QQmlEngine *engine);
    static class AsemanTextTools *textTools();
    static class AsemanCalendarConverter *calendar(QQmlEngine *engine);
    static class AsemanBackHandler *backHandler(QQmlEngine *engine);

    static void exportDocuments(const QString &destination);

protected:
    template<typename T>
    static QString exportItem(const QString &module, int major, int minor, const QString &component, bool store = true);
    template<typename T>
    static QString exportModel(const QString &module, int major, int minor, const QString &component);

    static QString fixType(const QString &type);

private:
#ifdef ASEMAN_STATIC_BUILD
    static bool static_types_registered;
#endif
};

#endif // ASEMANQTTOOLS_H
