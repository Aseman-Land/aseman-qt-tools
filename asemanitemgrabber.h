/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    Meikade is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Meikade is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANITEMGRABBER_H
#define ASEMANITEMGRABBER_H

#include <QObject>
#include <QQuickItem>

class AsemanItemGrabberPrivate;
class AsemanItemGrabber : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    AsemanItemGrabber(QObject *parent = 0);
    ~AsemanItemGrabber();

    void setItem(QQuickItem *item);
    QQuickItem *item() const;

    void setSuffix(const QString &suffix);
    QString suffix() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

public slots:
    void save(const QString &dest, const QSize &size);

signals:
    void itemChanged();
    void suffixChanged();
    void fileNameChanged();
    void saved(const QString &dest);
    void failed();

private slots:
    void ready();

private:
    AsemanItemGrabberPrivate *p;
};

#endif // ASEMANITEMGRABBER_H
