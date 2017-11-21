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

#ifndef ASEMANNULLSTOREMANAGERCORE_H
#define ASEMANNULLSTOREMANAGERCORE_H

#include "asemanabstractstoremanagercore.h"

#include "asemantools_global.h"

class AsemanNullStoreManagerCorePrivate;
class LIBASEMANTOOLSSHARED_EXPORT AsemanNullStoreManagerCore : public AsemanAbstractStoreManagerCore
{
    Q_OBJECT
public:
    AsemanNullStoreManagerCore();
    virtual ~AsemanNullStoreManagerCore();

    void setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath);
    void updateStates();

    bool containsInventory(const QString &sku);
    void insertInventory(const QString &sku, bool state);
    void insertInventory(const QString &sku);
    void removeInventory(const QString &sku);
    bool getState(const QString &sku);
    int count();
    void clear();
    void purchaseInventory(const QString &sku);
    QStringList inventories();
    QMap<QString,AsemanStoreManagerInventoryItem> itemDetails() const;

private:
    AsemanNullStoreManagerCorePrivate *p;
};

#endif // ASEMANNULLSTOREMANAGERCORE_H
