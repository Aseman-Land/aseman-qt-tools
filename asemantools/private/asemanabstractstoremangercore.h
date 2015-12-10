#ifndef ASEMANABSTRACTSTOREMANGERCORE_H
#define ASEMANABSTRACTSTOREMANGERCORE_H

#include <QObject>
#include <QStringList>

class AsemanAbstractStoreMangerCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractStoreMangerCore();
    ~AsemanAbstractStoreMangerCore();

    virtual void setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath) = 0;

    virtual bool containsInventory(const QString &sku) = 0;
    virtual void insertInventory(const QString &sku, bool state) = 0;
    virtual void insertInventory(const QString &sku) = 0;
    virtual void removeInventory(const QString &sku) = 0;
    virtual bool getState(const QString &sku) = 0;
    virtual int count() = 0;

    virtual QStringList inventories() = 0;

public slots:
    virtual void updateStates() = 0;

signals:
    void inventoryStateChanged(const QString &sku, bool state);
    void setupFinished(bool state);
};

#endif // ASEMANABSTRACTSTOREMANGERCORE_H
