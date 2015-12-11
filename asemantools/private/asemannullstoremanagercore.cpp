#include "asemannullstoremanagercore.h"

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

AsemanNullStoreManagerCore::~AsemanNullStoreManagerCore()
{
    delete p;
}

