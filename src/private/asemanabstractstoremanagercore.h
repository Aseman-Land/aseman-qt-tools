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

#ifndef ASEMANABSTRACTSTOREMANAGERCORE_H
#define ASEMANABSTRACTSTOREMANAGERCORE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class AsemanStoreManagerInventoryItem;
class AsemanAbstractStoreManagerCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractStoreManagerCore();
    virtual ~AsemanAbstractStoreManagerCore();

    virtual void setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath) = 0;

    virtual bool containsInventory(const QString &sku) = 0;
    virtual void insertInventory(const QString &sku, bool state) = 0;
    virtual void insertInventory(const QString &sku) = 0;
    virtual void removeInventory(const QString &sku) = 0;
    virtual bool getState(const QString &sku) = 0;
    virtual int count() = 0;
    virtual void clear() = 0;
    virtual void purchaseInventory(const QString &sku) = 0;

    virtual QStringList inventories() = 0;
    virtual QMap<QString,AsemanStoreManagerInventoryItem> itemDetails() const = 0;

public slots:
    virtual void updateStates() = 0;

signals:
    void inventoryStateChanged(const QString &sku, bool state);
    void setupFinished(bool state);
    void itemDetailsChanged();
};

#endif // ASEMANABSTRACTSTOREMANAGERCORE_H
