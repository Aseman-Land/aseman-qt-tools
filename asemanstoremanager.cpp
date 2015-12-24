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

QPointer<AsemanAbstractStoreManagerCore> aseman_store_manager_core;

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
}

void AsemanStoreManager::setPublicKey(const QString &publicKey)
{
    if(p->publicKey == publicKey)
        return;

    p->publicKey = publicKey;
    emit publicKeyChanged();
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
    emit packageNameChanged();
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
    emit bindIntentChanged();
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

    emit cacheSourceChanged();
}

QString AsemanStoreManager::cacheSource() const
{
    return p->cacheSource;
}

bool AsemanStoreManager::setup()
{
    if(p->publicKey.isEmpty() || p->packageName.isEmpty() || p->bindIntent.isEmpty())
        return false;

    initCore();
    initProperties();
    aseman_store_manager_core->setup(p->publicKey, p->packageName, p->bindIntent);
    return true;
}

void AsemanStoreManager::inventoryStateChanged(const QString &sku, bool state)
{
    setProperty(sku.toUtf8(), INVENTORY_STATE(state));
    if(p->settings)
        p->settings->setValue(INVENTORY_CACHE_KEY(sku), state);
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
    if(aseman_store_manager_core->getState(propertyName))
        return;

    aseman_store_manager_core->purchaseInventory(propertyName);
}

void AsemanStoreManager::initProperties()
{
    initCore();
    aseman_store_manager_core->clear();
    const QMetaObject *meta = metaObject();
    for(int i=0; i<meta->propertyCount(); i++)
    {
        if(meta->property(i).type() != QVariant::Int)
            continue;

        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        const QByteArray &signalSign = property.notifySignal().methodSignature();

        aseman_store_manager_core->insertInventory(propertyName);

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
    if(!aseman_store_manager_core)
        aseman_store_manager_core = new AsemanStoreManagerCore();
    if(p->core == aseman_store_manager_core)
        return;
    if(p->core)
        disconnect(p->core.data(), SIGNAL(inventoryStateChanged(QString,bool)),
                   this, SLOT(inventoryStateChanged(QString,bool)));

    p->core = aseman_store_manager_core;
    if(p->core)
        connect(p->core.data(), SIGNAL(inventoryStateChanged(QString,bool)),
                this, SLOT(inventoryStateChanged(QString,bool)));
}

AsemanStoreManager::~AsemanStoreManager()
{
    delete p;
}

