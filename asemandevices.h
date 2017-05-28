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

#ifndef ASEMANDEVICES_H
#define ASEMANDEVICES_H

#include <QObject>
#include <QUrl>
#include <QSize>

class AsemanMimeData;
class QScreen;
class AsemanDevicesPrivate;
class AsemanDevices : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isMobile       READ isMobile       NOTIFY isMobileChanged       )
    Q_PROPERTY(bool isTablet       READ isTablet       NOTIFY isTabletChanged       )
    Q_PROPERTY(bool isLargeTablet  READ isLargeTablet  NOTIFY isLargeTabletChanged  )
    Q_PROPERTY(bool isTouchDevice  READ isTouchDevice  NOTIFY isTouchDeviceChanged  )
    Q_PROPERTY(bool isDesktop      READ isDesktop      NOTIFY isDesktopChanged      )
    Q_PROPERTY(bool isMacX         READ isMacX         NOTIFY isMacXChanged         )
    Q_PROPERTY(bool isWindows      READ isWindows      NOTIFY isWindowsChanged      )
    Q_PROPERTY(bool isWindows8     READ isWindows8     NOTIFY isWindowsChanged      )
    Q_PROPERTY(bool isLinux        READ isLinux        NOTIFY isLinuxChanged        )
    Q_PROPERTY(bool isAndroid      READ isAndroid      NOTIFY isAndroidChanged      )
    Q_PROPERTY(bool isIOS          READ isIOS          NOTIFY isIOSChanged          )
    Q_PROPERTY(bool isUbuntuTouch  READ isUbuntuTouch  NOTIFY isUbuntuTouchChanged  )
    Q_PROPERTY(bool isWindowsPhone READ isWindowsPhone NOTIFY isWindowsPhoneChanged )

    Q_PROPERTY(QObject* screen READ screenObj NOTIFY screenChanged )

    Q_PROPERTY(bool cameraIsAvailable READ cameraIsAvailable NOTIFY cameraIsAvailableChanged)

    Q_PROPERTY(qreal lcdPhysicalSize   READ lcdPhysicalSize   NOTIFY lcdPhysicalSizeChanged   )
    Q_PROPERTY(qreal lcdPhysicalWidth  READ lcdPhysicalWidth  NOTIFY lcdPhysicalWidthChanged  )
    Q_PROPERTY(qreal lcdPhysicalHeight READ lcdPhysicalHeight NOTIFY lcdPhysicalHeightChanged )
    Q_PROPERTY(qreal lcdDpiX           READ lcdDpiX           NOTIFY lcdDpiXChanged           )
    Q_PROPERTY(qreal lcdDpiY           READ lcdDpiY           NOTIFY lcdDpiYChanged           )

    Q_PROPERTY(QSize screenSize        READ screenSize        NOTIFY geometryChanged          )
    Q_PROPERTY(qreal keyboardHeight    READ keyboardHeight    NOTIFY geometryChanged          )

    Q_PROPERTY(QString localFilesPrePath READ localFilesPrePath NOTIFY localFilesPrePathChanged)

    Q_PROPERTY(int   densityDpi    READ densityDpi    NOTIFY densityDpiChanged  )
    Q_PROPERTY(qreal density       READ density       NOTIFY densityChanged     )
    Q_PROPERTY(qreal deviceDensity READ deviceDensity NOTIFY densityChanged     )
    Q_PROPERTY(qreal fontDensity   READ fontDensity   NOTIFY fontDensityChanged )

    Q_PROPERTY(bool  transparentStatusBar     READ transparentStatusBar     NOTIFY transparentStatusBarChanged    )
    Q_PROPERTY(bool  transparentNavigationBar READ transparentNavigationBar NOTIFY transparentNavigationBarChanged)
    Q_PROPERTY(qreal standardTitleBarHeight   READ standardTitleBarHeight   NOTIFY standardTitleBarHeightChanged  )
    Q_PROPERTY(qreal statusBarHeight          READ statusBarHeight          NOTIFY statusBarHeightChanged)
    Q_PROPERTY(qreal navigationBarHeight      READ navigationBarHeight      NOTIFY navigationBarHeightChanged)

    Q_PROPERTY(QString     clipboard    READ clipboard    WRITE setClipboard    NOTIFY clipboardChanged   )
    Q_PROPERTY(QList<QUrl> clipboardUrl READ clipboardUrl WRITE setClipboardUrl NOTIFY clipboardUrlChanged)

    Q_PROPERTY(bool keyboard READ keyboard NOTIFY keyboardChanged)

    Q_PROPERTY(QString cameraLocation    READ cameraLocation    NOTIFY cameraLocationChanged    )
    Q_PROPERTY(QString picturesLocation  READ picturesLocation  NOTIFY picturesLocationChanged  )
    Q_PROPERTY(QString musicsLocation    READ musicsLocation    NOTIFY musicsLocationChanged    )
    Q_PROPERTY(QString documentsLocation READ documentsLocation NOTIFY documentsLocationChanged )
    Q_PROPERTY(QString downloadsLocation READ downloadsLocation NOTIFY downloadsLocationChanged )
    Q_PROPERTY(QString resourcePath      READ resourcePathQml   NOTIFY resourcePathChanged      )
    Q_PROPERTY(QString libsPath          READ libsPath          NOTIFY libsPathChanged          )

    Q_PROPERTY(QString deviceName READ deviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QString deviceId   READ deviceId   NOTIFY deviceIdChanged)
    Q_PROPERTY(QString deviceShortId   READ deviceShortId   NOTIFY deviceIdChanged)

    Q_PROPERTY(QString qtVersion READ qtVersion NOTIFY qtVersionChanged)
    Q_PROPERTY(qreal qtMajorVersion READ qtMajorVersion NOTIFY qtVersionChanged)

    Q_PROPERTY(qreal fontScale READ fontScale WRITE setFontScale NOTIFY fontScaleChanged)

public:
    enum Flags {
        DisableDensities,
        AsemanScaleFactorEnable
    };

    AsemanDevices(QObject *parent = 0);
    ~AsemanDevices();

    static bool isMobile();
    static bool isTablet();
    static bool isLargeTablet();
    static bool isTouchDevice();
    static bool isDesktop();
    static bool isMacX();
    static bool isWindows();
    static bool isLinux();
    static bool isAndroid();
    static bool isIOS();
    static bool isUbuntuTouch();
    static bool isWindowsPhone();
    static bool isWindows8();

    static QScreen *screen();
    QObject *screenObj() const;

    static qreal lcdPhysicalSize();
    static qreal lcdPhysicalWidth();
    static qreal lcdPhysicalHeight();
    static qreal lcdDpiX();
    static qreal lcdDpiY();

    static QSize screenSize();
    qreal keyboardHeight() const;
    static QString deviceName();
    static QString deviceId();
    static QString deviceShortId();

    static QString qtVersion();
    static qreal qtMajorVersion();

    static int densityDpi();
    static qreal density();
    static qreal deviceDensity();
    static qreal fontDensity();

    static void setFontScale(qreal fontScale);
    static qreal fontScale();

    bool cameraIsAvailable() const;

    static QString localFilesPrePath();

    static bool transparentStatusBar();
    static bool transparentNavigationBar();
    qreal standardTitleBarHeight() const;

    static qreal statusBarHeight();
    static qreal navigationBarHeight();

    Q_INVOKABLE static void setFlag(int flag, bool state = true);
    Q_INVOKABLE static bool flag(int flag);

    QString clipboard() const;
    bool keyboard() const;

    QList<QUrl> clipboardUrl() const;
    void setClipboardUrl(const QList<QUrl> &urls);

    static QString cameraLocation();
    static QString picturesLocation();
    static QString musicsLocation();
    static QString documentsLocation();
    static QString downloadsLocation();
    static QString resourcePath();
    static QString resourcePathQml();
    static QString libsPath();

public slots:
    void hideKeyboard();
    void showKeyboard();

    void share(const QString & subject, const QString & message );
    void openFile( const QString & address );
    void shareFile(const QString &address);
    void callNumber( const QString & number );
    void setClipboard( const QString & text );
    void setClipboardData(AsemanMimeData *mime);

    bool startCameraPicture();
    bool getOpenPictures();

signals:
    void incomingShare( const QString & title, const QString & msg );
    void incomingImage( const QString & path );
    void selectImageResult( const QString & path );
    void activityPaused();
    void activityResumed();

    void isMobileChanged();
    void isTabletChanged();
    void isLargeTabletChanged();
    void isTouchDeviceChanged();
    void isDesktopChanged();
    void isMacXChanged();
    void isWindowsChanged();
    void isLinuxChanged();
    void isAndroidChanged();
    void isIOSChanged();
    void isUbuntuTouchChanged();
    void isWindowsPhoneChanged();

    void deviceNameChanged();
    void deviceIdChanged();
    void qtVersionChanged();

    void cameraIsAvailableChanged();

    void screenChanged();
    void localFilesPrePathChanged();

    void lcdPhysicalSizeChanged();
    void lcdPhysicalWidthChanged();
    void lcdPhysicalHeightChanged();

    void lcdDpiXChanged();
    void lcdDpiYChanged();

    void geometryChanged();

    void transparentStatusBarChanged();
    void transparentNavigationBarChanged();
    void standardTitleBarHeightChanged();
    void statusBarHeightChanged();
    void navigationBarHeightChanged();

    void densityDpiChanged();
    void densityChanged();
    void fontScaleChanged();
    void fontDensityChanged();

    void clipboardChanged();
    void clipboardUrlChanged();
    void keyboardChanged();

    void cameraLocationChanged();
    void picturesLocationChanged();
    void musicsLocationChanged();
    void documentsLocationChanged();
    void downloadsLocationChanged();
    void resourcePathChanged();
    void libsPathChanged();

private slots:
    void incoming_share( const QString & title, const QString & msg );
    void incoming_image( const QString & path );
    void select_image_result( const QString & path );
    void activity_paused();
    void activity_resumed();
    void keyboard_changed();

protected:
    void timerEvent(QTimerEvent *e);

private:
    AsemanDevicesPrivate *p;
};

#endif // ASEMANDEVICES_H
