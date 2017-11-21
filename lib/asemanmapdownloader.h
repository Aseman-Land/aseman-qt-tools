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

#ifndef ASEMANMAPDOWNLOADER_H
#define ASEMANMAPDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QSize>
#ifdef QT_POSITIONING_LIB
#include <QGeoCoordinate>
#define GEO_CLASS_NAME QGeoCoordinate
#else
#include <QPointF>
#define GEO_CLASS_NAME QPointF
#endif

#include "asemantools_global.h"

class AsemanMapDownloaderPrivate;
class LIBASEMANTOOLSSHARED_EXPORT AsemanMapDownloader : public QObject
{
    Q_OBJECT
    Q_ENUMS(MapProvider)

    Q_PROPERTY(QUrl destination READ destination WRITE setDestination NOTIFY destinationChanged)
    Q_PROPERTY(QUrl image READ image NOTIFY imageChanged)
    Q_PROPERTY(GEO_CLASS_NAME currentGeo READ currentGeo NOTIFY currentGeoChanged)
    Q_PROPERTY(int mapProvider READ mapProvider WRITE setMapProvider NOTIFY mapProviderChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(int zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(bool downloading READ downloading NOTIFY downloadingChanged)

public:
    enum MapProvider {
        MapProviderGoogle = 0
    };

    AsemanMapDownloader(QObject *parent = 0);
    virtual ~AsemanMapDownloader();

    void setDestination(const QUrl &dest);
    QUrl destination() const;

    void setMapProvider(int type);
    int mapProvider() const;

    void setSize(const QSize &size);
    QSize size() const;

    void setZoom(int zoom);
    int zoom() const;

    GEO_CLASS_NAME currentGeo() const;
    QUrl image() const;

    bool downloading() const;

public Q_SLOTS:
#ifdef QT_POSITIONING_LIB
    void download(const QPointF &geo);
    bool check(const QPointF &geo);
    QString linkOf(const QPointF &geo);
    QString webLinkOf(const QPointF &geo);
    QString pathOf(const QPointF &geo);
#endif
    void download(const GEO_CLASS_NAME &geo);
    bool check(const GEO_CLASS_NAME &geo);
    QString linkOf(const GEO_CLASS_NAME &geo);
    QString webLinkOf(const GEO_CLASS_NAME &geo);
    QString pathOf(const GEO_CLASS_NAME &geo);

Q_SIGNALS:
    void destinationChanged();
    void currentGeoChanged();
    void imageChanged();
    void mapProviderChanged();
    void sizeChanged();
    void zoomChanged();
    void finished();
    void downloadingChanged();

private Q_SLOTS:
    void finishedSlt( const QByteArray & data );

private:
    void init_downloader();

private:
    AsemanMapDownloaderPrivate *p;
};

#endif // ASEMANMAPDOWNLOADER_H
