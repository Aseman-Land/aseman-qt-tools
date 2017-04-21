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

#include "asemanitemgrabber.h"

#include <QPointer>
#include <QQuickItemGrabResult>
#include <QImageWriter>
#include <QDir>
#include <QUuid>

class AsemanItemGrabberPrivate
{
public:
    QPointer<QQuickItem> item;
    QSharedPointer<QQuickItemGrabResult> result;
    QString dest;
};

AsemanItemGrabber::AsemanItemGrabber(QObject *parent) :
    QObject(parent)
{
    p = new AsemanItemGrabberPrivate;
}

void AsemanItemGrabber::setItem(QQuickItem *item)
{
    if(p->item == item)
        return;

    p->item = item;
    emit itemChanged();
}

QQuickItem *AsemanItemGrabber::item() const
{
    return p->item;
}

void AsemanItemGrabber::save(const QString &dest, const QSize &size)
{
    if(!p->item)
    {
        emit failed();
        return;
    }

    p->result = p->item->grabToImage(size);
    if(!p->result)
    {
        emit failed();
        return;
    }

    connect(p->result.data(), SIGNAL(ready()), this, SLOT(ready()));

    QDir().mkpath(dest);
    p->dest = dest + "/" + QUuid::createUuid().toString().remove("{").remove("}") + ".png";
}

void AsemanItemGrabber::ready()
{
    disconnect(p->result.data(), SIGNAL(ready()), this, SLOT(ready()));

    const QImage & img = p->result->image();

    QImageWriter writer(p->dest);
    writer.write(img);

    emit saved(p->dest);
}

AsemanItemGrabber::~AsemanItemGrabber()
{
    delete p;
}
