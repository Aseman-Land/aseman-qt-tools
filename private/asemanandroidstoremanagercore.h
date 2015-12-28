#ifndef ASEMANANDROIDSTOREMANAGERCORE_H
#define ASEMANANDROIDSTOREMANAGERCORE_H

#include "asemanabstractstoremanagercore.h"

class AsemanAndroidStoreManagerCorePrivate;
class AsemanAndroidStoreManagerCore : public AsemanAbstractStoreManagerCore
{
    Q_OBJECT
public:
    AsemanAndroidStoreManagerCore();
    ~AsemanAndroidStoreManagerCore();

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
    QMap<QString, AsemanStoreManagerInventoryItem> itemDetails() const;

public slots:
    void detailsFetched(const QString &sku, const QString &type, const QString &price, const QString &title, const QString &description);

private:
    AsemanAndroidStoreManagerCorePrivate *p;
};

#endif // ASEMANANDROIDSTOREMANAGERCORE_H
