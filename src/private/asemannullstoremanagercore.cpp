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

#include "asemannullstoremanagercore.h"
#include "../asemanstoremanager.h"

#include <QMap>

class AsemanNullStoreManagerCorePrivate
{
public:
    QMap<QString, bool> data;
};

AsemanNullStoreManagerCore::AsemanNullStoreManagerCore() :
    AsemanAbstractStoreManagerCore()
{
    p = new AsemanNullStoreManagerCorePrivate;
}

void AsemanNullStoreManagerCore::setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath)
{
    Q_UNUSED(base64EncodedPublicKey)
    Q_UNUSED(storePackageName)
    Q_UNUSED(billingBindIntentPath)
}

void AsemanNullStoreManagerCore::updateStates()
{
}

bool AsemanNullStoreManagerCore::containsInventory(const QString &sku)
{
    return p->data.contains(sku);
}

void AsemanNullStoreManagerCore::insertInventory(const QString &sku, bool state)
{
    p->data.insert(sku, state);
}

void AsemanNullStoreManagerCore::insertInventory(const QString &sku)
{
    if(!containsInventory(sku))
        insertInventory(sku, false);
}

void AsemanNullStoreManagerCore::removeInventory(const QString &sku)
{
    p->data.remove(sku);
}

bool AsemanNullStoreManagerCore::getState(const QString &sku)
{
    return p->data.value(sku);
}

int AsemanNullStoreManagerCore::count()
{
    return p->data.count();
}

void AsemanNullStoreManagerCore::clear()
{
    p->data.clear();
}

void AsemanNullStoreManagerCore::purchaseInventory(const QString &sku)
{
    Q_UNUSED(sku)
}

QStringList AsemanNullStoreManagerCore::inventories()
{
    return p->data.keys();
}

QMap<QString, AsemanStoreManagerInventoryItem> AsemanNullStoreManagerCore::itemDetails() const
{
    return QMap<QString,AsemanStoreManagerInventoryItem>();
}

AsemanNullStoreManagerCore::~AsemanNullStoreManagerCore()
{
    delete p;
}
