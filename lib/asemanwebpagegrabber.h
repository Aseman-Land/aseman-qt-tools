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

#ifndef ASEMANWEBPAGEGRABBER_H
#define ASEMANWEBPAGEGRABBER_H

#include "asemanquickobject.h"
#include <QUrl>

class AsemanWebPageGrabberPrivate;
class AsemanWebPageGrabber : public AsemanQuickObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
    Q_PROPERTY(int timeOut READ timeOut WRITE setTimeOut NOTIFY timeOutChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(bool isAvailable READ isAvailable NOTIFY isAvailableChanged)

public:
    AsemanWebPageGrabber(QObject *parent = 0);
    virtual ~AsemanWebPageGrabber();

    void setSource(const QUrl &source);
    QUrl source() const;

    void setDestination(const QString &dest);
    QString destination() const;

    void setTimeOut(int ms);
    int timeOut() const;

    bool running() const;
    bool isAvailable() const;

public Q_SLOTS:
    void start(bool force = false);
    QUrl check(const QUrl &source, QString *destPath = 0);

Q_SIGNALS:
    void complete(const QImage &image);
    void finished(const QUrl &path);

    void sourceChanged();
    void destinationChanged();
    void timeOutChanged();
    void runningChanged();
    void isAvailableChanged();

private Q_SLOTS:
    void completedSlt();
    void loadProgress(int p);

    void createWebView();
    void destroyWebView();

private:
    AsemanWebPageGrabberPrivate *p;
};

#endif // ASEMANWEBPAGEGRABBER_H
