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

#ifndef ASEMANSTOREMANAGER_H
#define ASEMANSTOREMANAGER_H

#include <QObject>
#include <QList>
#include <QPointer>

#include "asemanquickobject.h"

#define DEFINE_STORE_MANAGER_INVENTORY(SKU) \
    DEFINE_QML_PROEPRTY(int, SKU) \
    Q_SIGNALS: \
        void SKU##_fakeSignal(); \
    public: \
        Q_PROPERTY(bool SKU##_IsPurchased READ SKU##_IsPurchased NOTIFY SKU##Changed) \
        Q_PROPERTY(bool SKU##_IsPurchasing READ SKU##_IsPurchasing NOTIFY SKU##Changed) \
        Q_PROPERTY(QString SKU##_Price READ SKU##_Price NOTIFY SKU##_fakeSignal) \
        Q_PROPERTY(QString SKU##_Title READ SKU##_Title NOTIFY SKU##_fakeSignal) \
        Q_PROPERTY(QString SKU##_Description READ SKU##_Description NOTIFY SKU##_fakeSignal) \
        Q_PROPERTY(QString SKU##_Type READ SKU##_Type NOTIFY SKU##_fakeSignal) \
        Q_PROPERTY(QString SKU##_Sku READ SKU##_Sku NOTIFY SKU##_fakeSignal) \
        bool SKU##_IsPurchased() const { return SKU() == AsemanStoreManager::InventoryStatePurchased; } \
        bool SKU##_IsPurchasing() const { return SKU() == AsemanStoreManager::InventoryStatePurchasing; } \
        QString SKU##_Price() const { return detail(#SKU).price; } \
        QString SKU##_Title() const { return detail(#SKU).title; } \
        QString SKU##_Description() const { return detail(#SKU).description; } \
        QString SKU##_Type() const { return detail(#SKU).type; } \
        QString SKU##_Sku() const { return #SKU; }

#define CHECK_INVENTORY_PURCHASED(STORE, SKU) \
    (STORE && STORE->SKU##_IsPurchased())

class AsemanStoreManagerInventoryItem
{
public:
    QString sku;
    QString type;
    QString price;
    QString title;
    QString description;
};

class AsemanStoreManagerProduct;
class AsemanStoreManagerPrivate;
class AsemanStoreManager : public AsemanQuickObject
{
    Q_OBJECT
    Q_ENUMS(InventoryState)
    Q_PROPERTY(QString publicKey   READ publicKey   WRITE setPublicKey   NOTIFY publicKeyChanged  )
    Q_PROPERTY(QString packageName READ packageName WRITE setPackageName NOTIFY packageNameChanged)
    Q_PROPERTY(QString bindIntent  READ bindIntent  WRITE setBindIntent  NOTIFY bindIntentChanged )
    Q_PROPERTY(QString cacheSource READ cacheSource WRITE setCacheSource NOTIFY cacheSourceChanged)

    friend class AsemanStoreManagerProduct;

public:
    enum InventoryState {
        InventoryStateNone = 0,
        InventoryStatePurchasing,
        InventoryStatePurchased
    };

    AsemanStoreManager(QObject *parent = 0);
    virtual ~AsemanStoreManager();

    void setPublicKey(const QString &pkey);
    QString publicKey() const;

    void setPackageName(const QString &name);
    QString packageName() const;

    void setBindIntent(const QString &path);
    QString bindIntent() const;

    void setCacheSource(const QString &path);
    QString cacheSource() const;

    QMap<QString,AsemanStoreManagerInventoryItem> itemDetails() const;
    AsemanStoreManagerInventoryItem detail(const QString &sku) const;

    int inventoryState(const QString &sku) const;
    bool startPurchasing(const QString &sku);

public slots:
    bool setup();

signals:
    void publicKeyChanged();
    void packageNameChanged();
    void bindIntentChanged();
    void cacheSourceChanged();
    void itemDetailsChanged();
    void inventoryStateChanged(const QString &sku);
    void inventoryPurchased(const QString &sku);

private slots:
    void inventoryStateChanged_slt(const QString &sku, bool state);
    void propertyChanged();

protected:
    class AsemanAbstractStoreManagerCore *core();

private:
    void initProperties();
    void initItemChilds();
    void reinitCache();
    void initCore();

private:
    AsemanStoreManagerPrivate *p;
};


class AsemanStoreManagerProduct : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool IsPurchased READ IsPurchased NOTIFY skuChanged)
    Q_PROPERTY(bool IsPurchasing READ IsPurchasing NOTIFY skuChanged)
    Q_PROPERTY(QString price READ price NOTIFY fakeSignal)
    Q_PROPERTY(QString title READ title NOTIFY fakeSignal)
    Q_PROPERTY(QString description READ description NOTIFY fakeSignal)
    Q_PROPERTY(QString type READ type NOTIFY fakeSignal)
    Q_PROPERTY(QString sku READ sku WRITE setSku NOTIFY skuChanged)
    Q_PROPERTY(AsemanStoreManager* store READ store WRITE setStore NOTIFY storeChanged)

public:
    AsemanStoreManagerProduct(QObject *parent = Q_NULLPTR);
    virtual ~AsemanStoreManagerProduct();

    bool IsPurchased() const { return _skuState == AsemanStoreManager::InventoryStatePurchased; }
    bool IsPurchasing() const { return _skuState == AsemanStoreManager::InventoryStatePurchasing; }
    QString price() const { return detail(_sku).price; }
    QString title() const { return detail(_sku).title; }
    QString description() const { return detail(_sku).description; }
    QString type() const { return detail(_sku).type; }

    QString sku() const { return _sku; }
    void setSku(const QString &sku);

    AsemanStoreManager *store() const;
    void setStore(AsemanStoreManager *store);

Q_SIGNALS:
    void fakeSignal();
    void skuChanged();
    void storeChanged();

protected:
    AsemanStoreManagerInventoryItem detail(const QString &sku) const {
        if(store())
            return store()->detail(sku);
        else
            return AsemanStoreManagerInventoryItem();
    }

    void beginUpdate();
    void endUpdate();

private:
    QString _sku;
    int _skuState;
    QPointer<AsemanStoreManager> _store;
};

#endif // ASEMANSTOREMANAGER_H
