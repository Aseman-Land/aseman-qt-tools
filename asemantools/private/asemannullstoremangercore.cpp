#include "asemannullstoremangercore.h"

#include <QMap>

class AsemanNullStoreMangerCorePrivate
{
public:
    QMap<QString, bool> data;
};

AsemanNullStoreMangerCore::AsemanNullStoreMangerCore() :
    AsemanAbstractStoreMangerCore()
{
    p = new AsemanNullStoreMangerCorePrivate;
}

void AsemanNullStoreMangerCore::setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath)
{
    Q_UNUSED(base64EncodedPublicKey)
    Q_UNUSED(storePackageName)
    Q_UNUSED(billingBindIntentPath)
}

void AsemanNullStoreMangerCore::updateStates()
{
}

bool AsemanNullStoreMangerCore::containsInventory(const QString &sku)
{
    return p->data.contains(sku);
}

void AsemanNullStoreMangerCore::insertInventory(const QString &sku, bool state)
{
    p->data.insert(sku, state);
}

void AsemanNullStoreMangerCore::insertInventory(const QString &sku)
{
    if(!containsInventory(sku))
        insertInventory(sku, false);
}

void AsemanNullStoreMangerCore::removeInventory(const QString &sku)
{
    p->data.remove(sku);
}

bool AsemanNullStoreMangerCore::getState(const QString &sku)
{
    return p->data.value(sku);
}

int AsemanNullStoreMangerCore::count()
{
    return p->data.count();
}

QStringList AsemanNullStoreMangerCore::inventories()
{
    return p->data.keys();
}

AsemanNullStoreMangerCore::~AsemanNullStoreMangerCore()
{
    delete p;
}

