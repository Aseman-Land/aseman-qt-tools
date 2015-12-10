#ifndef ASEMANNULLSTOREMANGERCORE_H
#define ASEMANNULLSTOREMANGERCORE_H

#include "asemanabstractstoremangercore.h"

class AsemanNullStoreMangerCorePrivate;
class AsemanNullStoreMangerCore : public AsemanAbstractStoreMangerCore
{
    Q_OBJECT
public:
    AsemanNullStoreMangerCore();
    ~AsemanNullStoreMangerCore();

    void setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath);
    void updateStates();

    bool containsInventory(const QString &sku);
    void insertInventory(const QString &sku, bool state);
    void insertInventory(const QString &sku);
    void removeInventory(const QString &sku);
    bool getState(const QString &sku);
    int count();
    QStringList inventories();

private:
    AsemanNullStoreMangerCorePrivate *p;
};

#endif // ASEMANNULLSTOREMANGERCORE_H
