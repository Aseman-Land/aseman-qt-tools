#ifndef ASEMANNULLSTOREMANAGERCORE_H
#define ASEMANNULLSTOREMANAGERCORE_H

#include "asemanabstractstoremanagercore.h"

class AsemanNullStoreManagerCorePrivate;
class AsemanNullStoreManagerCore : public AsemanAbstractStoreManagerCore
{
    Q_OBJECT
public:
    AsemanNullStoreManagerCore();
    ~AsemanNullStoreManagerCore();

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

private:
    AsemanNullStoreManagerCorePrivate *p;
};

#endif // ASEMANNULLSTOREMANAGERCORE_H
