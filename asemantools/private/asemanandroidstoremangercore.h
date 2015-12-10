#ifndef ASEMANANDROIDSTOREMANGERCORE_H
#define ASEMANANDROIDSTOREMANGERCORE_H

#include "asemanabstractstoremangercore.h"

class AsemanAndroidStoreMangerCorePrivate;
class AsemanAndroidStoreMangerCore : public AsemanAbstractStoreMangerCore
{
    Q_OBJECT
public:
    AsemanAndroidStoreMangerCore();
    ~AsemanAndroidStoreMangerCore();

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
    AsemanAndroidStoreMangerCorePrivate *p;
};

#endif // ASEMANANDROIDSTOREMANGERCORE_H
