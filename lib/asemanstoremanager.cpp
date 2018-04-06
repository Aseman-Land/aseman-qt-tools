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

#define INVENTORY_CACHE_KEY(SKU) QString("Inventories/%1").arg(QString(SKU))
#define INVENTORY_STATE(STATE) (STATE?InventoryStatePurchased:InventoryStateNone)

#include "asemanstoremanager.h"
#include "private/asemanabstractstoremanagercore.h"

#include <QPointer>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QMetaObject>
#include <QMetaProperty>
#include <QHash>
#include <QSettings>

#ifdef Q_OS_ANDROID
#include "private/asemanandroidstoremanagercore.h"
typedef AsemanAndroidStoreManagerCore AsemanStoreManagerCore;
#else
#include "private/asemannullstoremanagercore.h"
typedef AsemanNullStoreManagerCore AsemanStoreManagerCore;
#endif

class AsemanStoreManagerPrivate
{
public:
    QString publicKey;
    QString packageName;
    QString bindIntent;
    QString cacheSource;
    QPointer<AsemanAbstractStoreManagerCore> core;
    QHash<QByteArray, QByteArray> signalsProperties;
    QSettings *settings;
};

AsemanStoreManager::AsemanStoreManager(QObject *parent) :
    AsemanQuickObject(parent)
{
    p = new AsemanStoreManagerPrivate;
    p->settings = 0;

    connect(this, &AsemanStoreManager::itemsChanged, this, &AsemanStoreManager::initItemChilds);
}

void AsemanStoreManager::setPublicKey(const QString &publicKey)
{
    if(p->publicKey == publicKey)
        return;

    p->publicKey = publicKey;
    Q_EMIT publicKeyChanged();
}

QString AsemanStoreManager::publicKey() const
{
    return p->publicKey;
}

void AsemanStoreManager::setPackageName(const QString &packageName)
{
    if(p->packageName == packageName)
        return;

    p->packageName = packageName;
    Q_EMIT packageNameChanged();
}

QString AsemanStoreManager::packageName() const
{
    return p->packageName;
}

void AsemanStoreManager::setBindIntent(const QString &bindIntent)
{
    if(p->bindIntent == bindIntent)
        return;

    p->bindIntent = bindIntent;
    Q_EMIT bindIntentChanged();
}

QString AsemanStoreManager::bindIntent() const
{
    return p->bindIntent;
}

void AsemanStoreManager::setCacheSource(const QString &path)
{
    if(p->cacheSource == path)
        return;

    p->cacheSource = path;
    reinitCache();

    Q_EMIT cacheSourceChanged();
}

QString AsemanStoreManager::cacheSource() const
{
    return p->cacheSource;
}

QMap<QString, AsemanStoreManagerInventoryItem> AsemanStoreManager::itemDetails() const
{
    if(!p->core)
        return QMap<QString, AsemanStoreManagerInventoryItem>();

    return p->core->itemDetails();
}

AsemanStoreManagerInventoryItem AsemanStoreManager::detail(const QString &sku) const
{
    if(!p->core)
        return AsemanStoreManagerInventoryItem();

    return p->core->itemDetails().value(sku);
}

int AsemanStoreManager::inventoryState(const QString &sku) const
{
    return property(sku.toUtf8()).toInt();
}

bool AsemanStoreManager::startPurchasing(const QString &sku)
{
    if(inventoryState(sku) != InventoryStateNone)
        return false;

    setProperty(sku.toUtf8(), static_cast<int>(InventoryStatePurchasing));
    return true;
}

bool AsemanStoreManager::setup()
{
    if(p->publicKey.isEmpty() || p->packageName.isEmpty() || p->bindIntent.isEmpty())
        return false;

    initCore();
    initProperties();
    initItemChilds();
    p->core->setup(p->publicKey, p->packageName, p->bindIntent);
    return true;
}

void AsemanStoreManager::inventoryStateChanged_slt(const QString &sku, bool state)
{
    const bool purchasing = (property(sku.toUtf8()).toInt() == InventoryStatePurchasing);
    setProperty(sku.toUtf8(), INVENTORY_STATE(state));
    if(p->settings)
        p->settings->setValue(INVENTORY_CACHE_KEY(sku), state);

    const bool purchased = (property(sku.toUtf8()).toInt() == InventoryStatePurchased);
    if(purchasing && purchased)
        Q_EMIT inventoryPurchased(sku);

    const QList<QObject*> &list = itemsList();
    for(QObject *obj: list)
    {
        AsemanStoreManagerProduct *prd = qobject_cast<AsemanStoreManagerProduct*>(obj);
        if(!prd || prd->store() != this) continue;
        if(prd->sku() == sku)
            Q_EMIT prd->skuChanged();
    }
}

void AsemanStoreManager::propertyChanged()
{
    if(sender() != this)
        return;

    const int signalIndex = senderSignalIndex();
    if(signalIndex == -1)
        return;

    QMetaMethod signalObj = metaObject()->method(signalIndex);
    const QByteArray &propertyName = p->signalsProperties.value(signalObj.methodSignature());
    Q_EMIT inventoryStateChanged(propertyName);

    const QVariant &value = property(propertyName);
    switch(value.toInt())
    {
    case InventoryStatePurchased:
    case InventoryStateNone:
        return;
        break;

    case InventoryStatePurchasing:
        break;
    }

    initCore();
    if(p->core->getState(propertyName))
        return;

    p->core->purchaseInventory(propertyName);
}

AsemanAbstractStoreManagerCore *AsemanStoreManager::core()
{
    initCore();
    return p->core;
}

void AsemanStoreManager::initProperties()
{
    initCore();
    p->core->clear();
    const QMetaObject *meta = metaObject();
    for(int i=0; i<meta->propertyCount(); i++)
    {
        if(meta->property(i).type() != QVariant::Int)
            continue;

        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        const QByteArray &signalSign = property.notifySignal().methodSignature();

        p->core->insertInventory(propertyName);

        p->signalsProperties[signalSign] = propertyName;
        if(p->settings)
        {
            bool state = p->settings->value( INVENTORY_CACHE_KEY(propertyName), false).toBool();
            setProperty(propertyName, INVENTORY_STATE(state));
        }

        connect(this, QByteArray::number(QSIGNAL_CODE)+signalSign,
                this, SLOT(propertyChanged()));
    }
}

void AsemanStoreManager::initItemChilds()
{
    const QList<QObject*> &list = itemsList();
    for(QObject *obj: list)
    {
        AsemanStoreManagerProduct *prd = qobject_cast<AsemanStoreManagerProduct*>(obj);
        if(!prd || prd->store()) continue;
        prd->setStore(this);
    }
}

void AsemanStoreManager::reinitCache()
{
    if(p->settings)
        delete p->settings;

    p->settings = 0;
    if(p->cacheSource.isEmpty())
        return;

    p->settings = new QSettings(p->cacheSource, QSettings::IniFormat, this);
}

void AsemanStoreManager::initCore()
{
    if(p->core)
        return;

    p->core = new AsemanStoreManagerCore();
    connect(p->core, &AsemanAbstractStoreManagerCore::inventoryStateChanged, this, &AsemanStoreManager::inventoryStateChanged_slt);
    connect(p->core, &AsemanAbstractStoreManagerCore::itemDetailsChanged, this, &AsemanStoreManager::itemDetailsChanged);
}

AsemanStoreManager::~AsemanStoreManager()
{
    delete p;
}



AsemanStoreManagerProduct::AsemanStoreManagerProduct(QObject *parent) :
    _skuState(AsemanStoreManager::InventoryStateNone)
{
    Q_UNUSED(parent)
}

AsemanStoreManager *AsemanStoreManagerProduct::store() const
{
    return _store;
}

void AsemanStoreManagerProduct::setStore(AsemanStoreManager *store)
{
    if(_store == store)
        return;

    beginUpdate();
    _store = store;
    endUpdate();

    Q_EMIT storeChanged();
}

void AsemanStoreManagerProduct::beginUpdate()
{
    if(_sku.isEmpty() || !_store)
        return;

    _store->core()->removeInventory(_sku);
    _store->core()->updateStates();
}

void AsemanStoreManagerProduct::endUpdate()
{
    if(_sku.isEmpty() || !_store)
        return;

    _store->core()->insertInventory(_sku);
    _store->core()->updateStates();
}

void AsemanStoreManagerProduct::setSku(const QString &sku)
{
    if(sku == _sku)
        return;

    beginUpdate();
    _sku = sku;
    endUpdate();

    Q_EMIT skuChanged();
}

AsemanStoreManagerProduct::~AsemanStoreManagerProduct()
{

}
