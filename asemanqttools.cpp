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

#include "asemanqttools.h"

#include "asemantoolsplugin.h"
#include "asemanquickview.h"
#include "asemandesktoptools.h"
#include "asemanqtlogger.h"
#include "asemandevices.h"
#include "asemantools.h"
#include "asemanapplication.h"
#include "asemanhashobject.h"
#include "asemandownloader.h"
#include "asemanlistobject.h"
#include "asemancalendarconverter.h"
#include "asemanimagecoloranalizor.h"
#include "asemansettings.h"
#include "asemanmimedata.h"
#include "asemandragobject.h"
#include "asemanbackhandler.h"
#include "aseman_macros.h"
#include "asemanfonthandler.h"
#include "asemancountriesmodel.h"
#include "asemanwindowdetails.h"
#include "asemanautostartmanager.h"
#include "asemanfilesystemmodel.h"
#include "asemanstoremanager.h"
#include "asemanhostchecker.h"
#include "asemannetworkmanager.h"
#include "asemannetworkmanageritem.h"
#include "asemannetworksleepmanager.h"
#include "asemanquickobject.h"
#include "asemannotification.h"
#include "asemantexttools.h"
#include "asemanfiledownloaderqueueitem.h"
#include "asemanquickitemimagegrabber.h"
#include "asemanwebpagegrabber.h"
#include "asemantitlebarcolorgrabber.h"
#include "asemanfiledownloaderqueue.h"
#include "asemanstoremanagermodel.h"
#include "asemantaskbarbutton.h"
#include "asemanmapdownloader.h"
#include "asemandragarea.h"
#include "asemanapplicationitem.h"
#include "asemancalendarmodel.h"
#include "asemanmixedlistmodel.h"
#include "asemanencrypter.h"
#include "asemanquickviewwrapper.h"
#include "asemanqmlsmartcomponent.h"
#include "asemanmouseeventlistener.h"
#include "asemancontributorsmodel.h"
#include "asemanqmlimage.h"
#include "asemantranslationmanager.h"
#include "asemansysteminfo.h"
#include "asemanitemgrabber.h"
#ifndef DISABLE_KEYCHAIN
#include "asemankeychain.h"
#endif
#ifdef QT_WIDGETS_LIB
#include "asemansystemtray.h"
#endif
#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif
#ifdef DESKTOP_LINUX
#include "asemanmimeapps.h"
#endif
#ifdef ASEMAN_SENSORS
#include "asemansensors.h"
#endif
#ifdef QZXING_SUPPORTED
#include "QZXing.h"
#ifdef QZXING_MULTIMEDIA
#include "QZXingFilter.h"
#endif
#endif
#ifdef ASEMAN_NOTIFICATION
#include "asemannotification.h"
#endif
#ifdef ASEMAN_MULTIMEDIA
#include "asemanaudiorecorder.h"
#include "asemanaudioencodersettings.h"
#endif
#if defined(Q_OS_LINUX) && defined(QT_DBUS_LIB)
#include "asemankdewallet.h"
#endif

#include <qqml.h>
#include <QHash>

#define SINGLETON_PROVIDER(TYPE, FNC_NAME, NEW_CREATOR) \
    static QObject *FNC_NAME(QQmlEngine *engine, QJSEngine *scriptEngine) { \
        Q_UNUSED(engine) \
        Q_UNUSED(scriptEngine) \
        static TYPE *singleton = NEW_CREATOR; \
        return singleton; \
    }

SINGLETON_PROVIDER(AsemanDevices            , aseman_devices_singleton         , AsemanQtTools::devices())
SINGLETON_PROVIDER(AsemanTools              , aseman_tools_singleton           , AsemanQtTools::tools())
SINGLETON_PROVIDER(AsemanTextTools          , aseman_text_tools_singleton      , AsemanQtTools::textTools())
SINGLETON_PROVIDER(AsemanDesktopTools       , aseman_desktoptools_singleton    , AsemanQtTools::desktopTools())
SINGLETON_PROVIDER(AsemanCalendarConverter  , aseman_calendarconv_singleton    , AsemanQtTools::calendar(engine))
SINGLETON_PROVIDER(AsemanBackHandler        , aseman_backhandler_singleton     , AsemanQtTools::backHandler(engine))
SINGLETON_PROVIDER(AsemanApplication        , aseman_app_singleton             , AsemanQtTools::application())
SINGLETON_PROVIDER(AsemanQuickViewWrapper   , aseman_qview_singleton           , AsemanQtTools::quickView(engine))
SINGLETON_PROVIDER(AsemanQtLogger           , aseman_logger_singleton          , AsemanQtTools::qtLogger())
SINGLETON_PROVIDER(AsemanSystemInfo         , aseman_sysinfo_singleton         , AsemanQtTools::systemInfo())
SINGLETON_PROVIDER(AsemanFileDownloaderQueue, aseman_downloader_queue_singleton, AsemanQtTools::getDownloaderQueue(engine))
#ifdef Q_OS_ANDROID
SINGLETON_PROVIDER(AsemanJavaLayer          , aseman_javalayer_singleton       , AsemanQtTools::javaLayer())
#endif

QStringList aseman_qt_tools_indexCache;
QString aseman_qt_tools_destination;

void AsemanQtTools::registerTypes(const char *uri, bool exportMode)
{
    static QSet<QByteArray> register_list;
    if(register_list.contains(uri) && !exportMode)
        return;
    qRegisterMetaType<AsemanMimeData*>("AsemanMimeData*");

    registerType<AsemanMimeData>(uri, 1, 0, "MimeData", exportMode);
    registerType<AsemanDragObject>(uri, 1, 0, "DragObject", exportMode);
    registerType<AsemanHashObject>(uri, 1,0, "HashObject", exportMode);
    registerType<AsemanListObject>(uri, 1,0, "ListObject", exportMode);
    registerType<AsemanDownloader>(uri, 1,0, "Downloader", exportMode);
    registerType<AsemanEncrypter>(uri, 1,0, "Encrypter", exportMode);
#ifndef DISABLE_KEYCHAIN
    registerType<AsemanKeychain>(uri, 1,0, "Keychain", exportMode);
#endif
#ifdef QT_WIDGETS_LIB
    registerType<AsemanSystemTray>(uri, 1,0, "SystemTray", exportMode);
#endif
    registerType<AsemanWindowDetails>(uri, 1,0, "WindowDetails", exportMode);
    registerType<AsemanQuickObject>(uri, 1,0, "AsemanObject", exportMode);
    registerType<AsemanImageColorAnalizor>(uri, 1,0, "ImageColorAnalizor", exportMode);
    registerType<AsemanNotification>(uri, 1,0, "Notification", exportMode);
    registerType<AsemanAutoStartManager>(uri, 1,0, "AutoStartManager", exportMode);
    registerType<AsemanSettings>(uri, 1,0, "Settings", exportMode);
    registerType<AsemanStoreManager>(uri, 1,0, "StoreManager", exportMode);
    registerType<AsemanStoreManagerProduct>(uri, 1,0, "StoreManagerProduct", exportMode);
    registerType<AsemanQuickItemImageGrabber>(uri, 1,0, "ItemImageGrabber", exportMode);
    registerType<AsemanFileDownloaderQueueItem>(uri, 1,0, "FileDownloaderQueueItem", exportMode);
    registerType<AsemanFileDownloaderQueue>(uri, 1,0, "FileDownloaderQueue", exportMode);
    registerType<AsemanMouseEventListener>(uri, 1,0, "MouseEventListener", exportMode);
    registerType<AsemanFontHandler>(uri, 1,0, "FontHandler", exportMode);
    registerType<AsemanItemGrabber>(uri, 1,0, "ItemGrabber", exportMode);
    registerType<AsemanApplication>(uri, 1,0, "AsemanApplication", exportMode);
    registerType<AsemanQmlImage>(uri, 1,0, "AsemanImage", exportMode);
    registerType<AsemanTranslationManager>(uri, 1,0, "TranslationManager", exportMode);
    registerType<AsemanQmlSmartComponent>(uri, 1,0, "SmartComponentCore", exportMode);
#ifdef DESKTOP_LINUX
    registerType<AsemanMimeApps>(uri, 1,0, "MimeApps", exportMode);
#endif
    registerType<AsemanWebPageGrabber>(uri, 1,0, "WebPageGrabber", exportMode);
    registerType<AsemanHostChecker>(uri, 1,0, "HostChecker", exportMode);
    registerType<AsemanNetworkManager>(uri, 1,0, "NetworkManager", exportMode);
    registerType<AsemanNetworkSleepManager>(uri, 1,0, "NetworkSleepManager", exportMode);
    registerType<AsemanTitleBarColorGrabber>(uri, 1,0, "TitleBarColorGrabber", exportMode);
    registerType<AsemanTaskbarButton>(uri, 1,0, "TaskbarButton", exportMode);
    registerType<AsemanMapDownloader>(uri, 1,0, "MapDownloader", exportMode);
    registerType<AsemanDragArea>(uri, 1,0, "MouseDragArea", exportMode);
    registerType<AsemanCalendarModel>(uri, 1,0, "CalendarModel", exportMode);
#if defined(Q_OS_LINUX) && defined(QT_DBUS_LIB)
    registerType<AsemanKdeWallet>(uri, 1,0, "KdeWallet", exportMode);
#endif

#ifdef ASEMAN_SENSORS
    registerType<AsemanSensors>(uri, 1,0, "AsemanSensors", exportMode);
#endif
#ifdef ASEMAN_MULTIMEDIA
    registerType<AsemanAudioRecorder>(uri, 1,0, "AudioRecorder", exportMode);
    registerType<AsemanAudioEncoderSettings>(uri, 1,0, "AudioEncoderSettings", exportMode);
#endif

    registerModel<AsemanMixedListModel>(uri, 1,0, "MixedListModel", exportMode);
    registerModel<AsemanCountriesModel>(uri, 1,0, "CountriesModel", exportMode);
    registerModel<AsemanFileSystemModel>(uri, 1,0, "FileSystemModel", exportMode);
    registerModel<AsemanStoreManagerModel>(uri, 1,0, "StoreManagerModel", exportMode);
    registerModel<AsemanContributorsModel>(uri, 1,0, "ContributorsModel", exportMode);

    registerSingletonType<AsemanDevices>(uri, 1, 0, "Devices", aseman_devices_singleton, exportMode);
    registerSingletonType<AsemanTextTools>(uri, 1, 0, "TextTools", aseman_text_tools_singleton, exportMode);
    registerSingletonType<AsemanTools>(uri, 1, 0, "Tools", aseman_tools_singleton, exportMode);
    registerSingletonType<AsemanDesktopTools>(uri, 1, 0, "Desktop", aseman_desktoptools_singleton, exportMode);
    registerSingletonType<AsemanCalendarConverter>(uri, 1, 0, "CalendarConv", aseman_calendarconv_singleton, exportMode);
    registerSingletonType<AsemanBackHandler>(uri, 1, 0, "BackHandler", aseman_backhandler_singleton, exportMode);
    registerSingletonType<AsemanApplication>(uri, 1, 0, "AsemanApp", aseman_app_singleton, exportMode);
    registerSingletonType<AsemanQtLogger>(uri, 1, 0, "Logger", aseman_logger_singleton, exportMode);
    registerSingletonType<AsemanQuickViewWrapper>(uri, 1, 0, "View", aseman_qview_singleton, exportMode);
    registerSingletonType<AsemanSystemInfo>(uri, 1, 0, "SystemInfo", aseman_sysinfo_singleton, exportMode);
    registerSingletonType<AsemanFileDownloaderQueue>(uri, 1, 0, "DownloaderQueue", aseman_downloader_queue_singleton, exportMode);
#ifdef Q_OS_ANDROID
    registerSingletonType<AsemanJavaLayer>(uri, 1, 0, "JavaLayer", aseman_javalayer_singleton, exportMode);
#endif

    registerUncreatableType<QScreen>(uri, 1, 0, "Screen", "", exportMode);
    registerUncreatableType<AsemanDesktopTools>(uri, 1,0, "AsemanDesktopTools", "It's a singleton class", exportMode);
    registerUncreatableType<AsemanNetworkManagerItem>(uri, 1,0, "NetworkManagerItem", "It must create using NetworkManager component.", exportMode);

#ifdef QZXING_SUPPORTED
    registerType<QZXing>(uri, 1, 0, "QZXing", exportMode);
#ifdef QZXING_MULTIMEDIA
    registerType<QZXingFilter>(uri, 1, 0, "QZXingFilter", exportMode);
#endif //QZXING_MULTIMEDIA
#endif

    register_list.insert(uri);
}

void AsemanQtTools::registerSecureTypes(const char *uri, bool exportMode)
{
    static QSet<QByteArray> register_list;
    if(register_list.contains(uri))
        return;

    registerUncreatableType<QScreen>(uri, 1, 0, "Screen", "", exportMode);
    registerUncreatableType<QWindow>(uri, 1, 0, "Window", "", exportMode);

    registerType<AsemanQuickObject>(uri, 1,0, "AsemanObject", exportMode);
    registerType<AsemanImageColorAnalizor>(uri, 1,0, "ImageColorAnalizor", exportMode);
    registerType<AsemanTitleBarColorGrabber>(uri, 1,0, "TitleBarColorGrabber", exportMode);
    registerType<AsemanFileDownloaderQueueItem>(uri, 1,0, "FileDownloaderQueueItem", exportMode);
    registerType<AsemanFileDownloaderQueue>(uri, 1,0, "FileDownloaderQueue", exportMode);
    registerType<AsemanWindowDetails>(uri, 1,0, "WindowDetails", exportMode);

    registerSingletonType<AsemanDevices>(uri, 1, 0, "Devices", aseman_devices_singleton, exportMode);
    registerSingletonType<AsemanDesktopTools>(uri, 1, 0, "Desktop", aseman_desktoptools_singleton, exportMode);
    registerSingletonType<AsemanBackHandler>(uri, 1, 0, "BackHandler", aseman_backhandler_singleton, exportMode);
    registerSingletonType<AsemanApplication>(uri, 1, 0, "AsemanApp", aseman_app_singleton, exportMode);

    register_list.insert(uri);
}

bool AsemanQtTools::safeRegisterTypes(const char *uri, QQmlEngine *engine)
{
    QString data = QString("import %1 %2.%3\nAsemanObject {}").arg(QString(uri)).arg(1).arg(0);
    QQmlComponent component(engine);
    component.setData(data.toUtf8(), QUrl());
    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
    if(item) /*! Test if registered before !*/
    {
        delete item;
        return false;
    }

    registerTypes(uri);
    registerSecureTypes( QString("%1.Secure").arg(QString(uri)).toUtf8() );
    engine->setImportPathList( QStringList()<< engine->importPathList() << "qrc:///asemantools/qml" );
    return true;
}

void AsemanQtTools::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_UNUSED(engine)
}

AsemanQuickViewWrapper *AsemanQtTools::quickView(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanQuickViewWrapper> > views;
    AsemanQuickViewWrapper *res = views.value(engine);
    if(res)
        return res;

    AsemanQuickView *view = new AsemanQuickView(engine, engine);
    if(view)
    {
        res = new AsemanQuickViewWrapper(view, engine);
        views[engine] = res;
        return res;
    }

    return res;
}

AsemanApplication *AsemanQtTools::application()
{
    static QPointer<AsemanApplication> res;
    if(!res)
        res = new AsemanApplication();

    return res;
}

AsemanDesktopTools *AsemanQtTools::desktopTools()
{
    static QPointer<AsemanDesktopTools> res = 0;
    if(!res)
        res = new AsemanDesktopTools();

    return res;
}

AsemanDevices *AsemanQtTools::devices()
{
    static QPointer<AsemanDevices> res = 0;
    if(!res)
        res = new AsemanDevices();

    return res;
}

AsemanQtLogger *AsemanQtTools::qtLogger()
{
    static QPointer<AsemanQtLogger> res = 0;
    if(!res)
    {
        QString path = QString::fromUtf8(qgetenv("ASEMAN_LOG_PATH"));
        if(path.isEmpty())
            path = AsemanApplication::logPath();

        res = new AsemanQtLogger(path);
    }

    return res;
}

#ifdef Q_OS_ANDROID
AsemanJavaLayer *AsemanQtTools::javaLayer()
{
    static QPointer<AsemanJavaLayer> res = 0;
    if(!res)
        res = new AsemanJavaLayer();

    return res;
}
#endif

AsemanTools *AsemanQtTools::tools()
{
    static QPointer<AsemanTools> res = 0;
    if(!res)
        res = new AsemanTools();

    return res;
}

AsemanSystemInfo *AsemanQtTools::systemInfo()
{
    static QPointer<AsemanSystemInfo> res = 0;
    if(!res)
        res = new AsemanSystemInfo();

    return res;
}

AsemanFileDownloaderQueue *AsemanQtTools::getDownloaderQueue(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanFileDownloaderQueue> > views;
    AsemanFileDownloaderQueue *res = views.value(engine);
    if(res)
        return res;

    res = new AsemanFileDownloaderQueue(engine);
    views[engine] = res;
    return res;
}

AsemanTextTools *AsemanQtTools::textTools()
{
    static QPointer<AsemanTextTools> res = 0;
    if(!res)
        res = new AsemanTextTools();

    return res;
}

AsemanCalendarConverter *AsemanQtTools::calendar(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanCalendarConverter> > views;
    AsemanCalendarConverter *res = views.value(engine);
    if(res)
        return res;

    res = new AsemanCalendarConverter();
    views[engine] = res;
    return res;
}

AsemanBackHandler *AsemanQtTools::backHandler(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanBackHandler> > views;
    AsemanBackHandler *res = views.value(engine);
    if(res)
        return res;

    res = new AsemanBackHandler();
    views[engine] = res;
    return res;
}

template<typename T>
int AsemanQtTools::registerType(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode)
{
    if(exportMode)
        exportItem<T>(uri, versionMajor, versionMinor, typeName);
    else
        return qmlRegisterType<T>(uri, versionMajor, versionMinor, typeName);
    return 0;
}

template<typename T>
int AsemanQtTools::registerModel(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode)
{
    if(exportMode)
        exportModel<T>(uri, versionMajor, versionMinor, typeName);
    else
        return qmlRegisterType<T>(uri, versionMajor, versionMinor, typeName);
    return 0;
}

template<typename T>
int AsemanQtTools::registerSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName, QObject *(*callback)(QQmlEngine *, QJSEngine *), bool exportMode)
{
    if(exportMode)
        exportItem<T>(uri, versionMajor, versionMinor, typeName);
    else
        return qmlRegisterSingletonType<T>(uri, versionMajor, versionMinor, typeName, callback);
    return 0;
}

template<typename T>
int AsemanQtTools::registerUncreatableType(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString &reason, bool exportMode)
{
    if(exportMode)
        exportItem<T>(uri, versionMajor, versionMinor, qmlName);
    else
        return qmlRegisterUncreatableType<T>(uri, versionMajor, versionMinor, qmlName, reason);
    return 0;
}


void AsemanQtTools::exportDocuments(const QString &destination)
{
    aseman_qt_tools_destination = destination;

    QDir().mkpath(aseman_qt_tools_destination);
    aseman_qt_tools_indexCache.clear();

    AsemanQtTools::registerTypes("AsemanTools", true);

    QString index = QString("# AsemanTools Documents\n\n");
    index += "### [Getting Started](gettingstarted.md)\n\n";
    index += "### How to import:\n\n";
    index += "```c++\nimport AsemanTools 1.0\n```\n\nor\n\n"
             "```c++\nimport AsemanTools 1.0 as Aseman\n```\n\n";
    index += "### Types\n\nHere are all components of the AsemanTools:\n\n";
    Q_FOREACH(const QString cmpnt, aseman_qt_tools_indexCache)
    {
        if(cmpnt == "MimeData")
            index += "\n##### Normal types\n\n";
        if(cmpnt == "MixedListModel")
            index += "\n##### Models\n\n";
        if(cmpnt == "Devices")
            index += "\n##### Singletons\n\n";
        if(cmpnt == "Screen")
            index += "\n##### Uncreatable types\n\n";
        index += QString(" * [%1](%2.md)\n").arg(cmpnt).arg(cmpnt.toLower());
    }

    QString path = aseman_qt_tools_destination + "/start.md";
    aseman_qt_tools_destination.clear();
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return;

    file.write(index.toUtf8());
    file.close();
}

QString AsemanQtTools::fixType(const QString &type)
{
    if(type == "QSizeF" || type == "QSize")
        return "size";
    if(type == "QPoint" || type == "QPointF")
        return "point";
    if(type == "QUrl")
        return "url";
    if(type == "QString")
        return "string";
    if(type == "QByteArray")
        return "byte";
    if(type == "bool")
        return "boolean";
    if(type == "double" || type == "qreal")
        return "real";
    if(type == "QVariant")
        return "variant";
    if(type == "QJSValue")
        return "function(){[code]}";
    if(type == "QVariantMap")
        return "map";
    if(type == "QVariantList")
        return "list&lt;variant&gt;";
    if(type == "QStringList")
        return "list&lt;string&gt;";
    if(type == "QList<qint32>")
        return "list&lt;int&gt;";
    if(type.contains("*"))
    {
        if(type == "QObject*")
            return "object";
        if(type.contains("Telegram"))
        {
            QString name = QString(type).remove("*").remove("Telegram");
            return QString("[%1](%2.md)").arg(name).arg(name.toLower());
        }
        if(type.contains("Object"))
        {
            QString name = QString(type).remove("*").remove("Object");
            return QString("[%1](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/%2.md)")
                    .arg(name).arg(name.toLower());
        }
        if(type == "QQmlComponent*")
            return "Component";
        if(type == "QQuickItem")
            return "Item";
    }
    if(type.contains("Telegram"))
    {
        QString name = QString(type).remove("Telegram");
        return QString("[%1](%2.md)").arg(name).arg(name.toLower());
    }
    if(type == "QQuickItem")
        return "Item";
    if(type == "QObject")
        return "object";
    if(type.contains("Object"))
    {
        QString name = QString(type).remove("Object");
        return QString("[%1](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/%2.md)")
                .arg(name).arg(name.toLower());
    }
    return type;
}

template<typename T>
QString AsemanQtTools::exportItem(const QString &module, int major, int minor, const QString &component, bool store)
{
    QString result;
    aseman_qt_tools_indexCache << component;

    QMetaObject meta = T::staticMetaObject;
    QString inherits = fixType(meta.superClass()? meta.superClass()->className() : "");
    bool isModel = component.toLower().contains("model");

    result += QString("# %1\n\n").arg(component);

    QString headers;
    headers += QString(" * [Component details](#component-details)\n");

    QString details = QString("\n### Component details:\n\n");
    details += QString("|Detail|Value|\n"
                       "|------|-----|\n");
    details += QString("|%1|%2 %3.%4|\n").arg("Import").arg(module).arg(major).arg(minor);
    details += QString("|%1|<font color='#074885'>%2</font>|\n").arg("Component").arg(component);
    details += QString("|%1|<font color='#074885'>%2</font>|\n").arg("C++ class").arg(meta.className());
    details += QString("|%1|<font color='#074885'>%2</font>|\n").arg("Inherits").arg(inherits);
    details += QString("|%1|<font color='#074885'>%2</font>|\n").arg("Model").arg(isModel?"Yes":"No");

    QString resultProperties;
    QStringList propertiesSignals;
    for(int i=0; i<meta.propertyCount(); i++)
    {
        QMetaProperty property = meta.property(i);
        const QString &propertyName = property.name();
        const QString &propertyType = fixType(property.typeName());
        propertiesSignals << property.notifySignal().name();

        QString text = QString("* <font color='#074885'><b>%1</b></font>: %2").arg(propertyName).arg(propertyType);
        if(!property.isWritable())
            text += " (readOnly)";

        text += "\n";
        if(meta.propertyOffset()<=i)
            resultProperties += text;
    }

    QString enumResults;
    for(int i=meta.enumeratorOffset(); i<meta.enumeratorCount(); i++)
    {
        QMetaEnum enumerator = meta.enumerator(i);
        const QString &enumName = enumerator.name();

        enumResults += QString("\n##### %1\n\n").arg(enumName);
        enumResults += QString("|Key|Value|\n"
                               "|---|-----|\n");

        for(int j=0; j<enumerator.keyCount(); j++)
            enumResults += QString("|%1|%2|\n").arg(enumerator.key(j)).arg(enumerator.value(j));
    }

    QString resultSlots;
    QString resultSignals;
    for(int i=meta.methodOffset(); i<meta.methodCount(); i++)
    {
        QMetaMethod method = meta.method(i);
        if(method.access() != QMetaMethod::Public)
            continue;

        const QString &methodName = method.name();
        if(propertiesSignals.contains(methodName))
            continue;

        const QString &methodType = fixType(method.typeName());

        QString args;
        const QList<QByteArray> &paramNames = method.parameterNames();
        const QList<QByteArray> &paramTypes = method.parameterTypes();
        for(int j=0; j<paramNames.count(); j++)
        {
            if(j != 0)
                args += ", ";

            args += fixType(paramTypes[j]) + " " + paramNames[j];
        }

        QString text = QString(" * %1 <font color='#074885'><b>%2</b></font>(%3)\n").arg(methodType).arg(methodName).arg(args);
        switch(static_cast<int>(method.methodType()))
        {
        case QMetaMethod::Slot:
            resultSlots += text;
            break;
        case QMetaMethod::Signal:
            resultSignals += text;
            break;
        }
    }

    if(!resultProperties.isEmpty())
    {
        headers += QString(" * [Normal Properties](#normal-properties)\n");
        resultProperties = QString("\n### Normal Properties\n\n") + resultProperties;
    }
    if(!enumResults.isEmpty())
    {
        headers += QString(" * [Enumerator](#enumerator)\n");
        enumResults = QString("\n### Enumerator\n\n") + enumResults;
    }
    if(!resultSlots.isEmpty())
    {
        headers += QString(" * [Methods](#methods)\n");
        resultSlots = QString("\n### Methods\n\n") + resultSlots;
    }
    if(!resultSignals.isEmpty())
    {
        headers += QString(" * [Signals](#signals)\n");
        resultSignals = QString("\n### Signals\n\n") + resultSignals;
    }
    if(isModel)
        headers += QString(" * [Roles](#roles)\n");

    result += headers + "\n";
    result += details + "\n";
    result += resultProperties + "\n";
    result += resultSlots + "\n";
    result += resultSignals + "\n";
    result += enumResults + "\n";

    if(!store)
        return result;

    QString path = aseman_qt_tools_destination + "/" + component.toLower() + ".md";
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return result;

    file.write(result.toUtf8());
    file.close();
    return result;
}

template<typename T>
QString AsemanQtTools::exportModel(const QString &module, int major, int minor, const QString &component)
{
    QString result = exportItem<T>(module, major, minor, component, false);
    T *model = new T();

    QHash<qint32,QByteArray> roleNames = model->roleNames();
    QMap<qint32,QByteArray> rolesMap;
    QHashIterator<qint32,QByteArray> i(roleNames);
    while(i.hasNext())
    {
        i.next();
        rolesMap[i.key()] = i.value();
    }

    result += "\n### Roles\n\n";
    Q_FOREACH(const QByteArray &name, rolesMap)
        result += QString(" * model.<font color='#074885'>%1</font>\n").arg(QString(name));

    delete model;

    QString path = aseman_qt_tools_destination + "/" + component.toLower() + ".md";
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return result;

    file.write(result.toUtf8());
    file.close();
    return result;
}
