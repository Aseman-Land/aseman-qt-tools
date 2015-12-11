#ifndef ASEMANABSTRACTSTOREMANAGERCORE_H
#define ASEMANABSTRACTSTOREMANAGERCORE_H

#include <QObject>
#include <QStringList>

class AsemanAbstractStoreManagerCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractStoreManagerCore();
    ~AsemanAbstractStoreManagerCore();

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

public slots:
    virtual void updateStates() = 0;

signals:
    void inventoryStateChanged(const QString &sku, bool state);
    void setupFinished(bool state);
};

#endif // ASEMANABSTRACTSTOREMANAGERCORE_H
