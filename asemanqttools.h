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
    static void registerTypes(const char *uri, bool exportMode = false);
    static void registerSecureTypes(const char *uri, bool exportMode = false);

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
};

#endif // ASEMANQTTOOLS_H
