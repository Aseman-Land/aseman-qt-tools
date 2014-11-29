/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    Kaqaz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Kaqaz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanhashobject.h"

#include <QList>
#include <QPair>
#include <QDebug>
#include <QDebug>

class AsemanHashObjectPrivate
{
public:
    QMultiHash<QString,QVariant> hash;
};

AsemanHashObject::AsemanHashObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanHashObjectPrivate;
}

void AsemanHashObject::insert(const QString &key, const QVariant &value)
{
    p->hash.insert(key,value);
}

void AsemanHashObject::insertMulti(const QString &key, const QVariant &value)
{
    p->hash.insertMulti(key,value);
}

void AsemanHashObject::remove(const QString &key)
{
    p->hash.remove(key);
}

void AsemanHashObject::remove(const QString &key, const QVariant &value)
{
    p->hash.remove(key,value);
}

QVariant AsemanHashObject::key(const QVariant &value)
{
    return p->hash.key(value);
}

QStringList AsemanHashObject::keys(const QVariant &value)
{
    return p->hash.keys(value);
}

QStringList AsemanHashObject::keys()
{
    return p->hash.keys();
}

QVariant AsemanHashObject::value(const QString &key)
{
    return p->hash.value(key);
}

QVariantList AsemanHashObject::values(const QString &key)
{
    return p->hash.values(key);
}

QVariant AsemanHashObject::containt(const QString &key)
{
    return p->hash.contains(key);
}

QVariant AsemanHashObject::containt(const QString &key, const QVariant &value)
{
    return p->hash.contains(key,value);
}

void AsemanHashObject::clear()
{
    p->hash.clear();
}

int AsemanHashObject::count()
{
    return p->hash.count();
}

AsemanHashObject::~AsemanHashObject()
{
    delete p;
}
