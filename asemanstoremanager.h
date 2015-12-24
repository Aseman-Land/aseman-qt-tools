#ifndef ASEMANSTOREMANAGER_H
#define ASEMANSTOREMANAGER_H

#include <QObject>
#include "asemanquickobject.h"

class AsemanStoreManagerPrivate;
class AsemanStoreManager : public AsemanQuickObject
{
    Q_OBJECT
    Q_ENUMS(InventoryState)
    Q_PROPERTY(QString publicKey   READ publicKey   WRITE setPublicKey   NOTIFY publicKeyChanged  )
    Q_PROPERTY(QString packageName READ packageName WRITE setPackageName NOTIFY packageNameChanged)
    Q_PROPERTY(QString bindIntent  READ bindIntent  WRITE setBindIntent  NOTIFY bindIntentChanged )
    Q_PROPERTY(QString cacheSource READ cacheSource WRITE setCacheSource NOTIFY cacheSourceChanged)

public:
    enum InventoryState {
        InventoryStateNone = 0,
        InventoryStatePurchasing,
        InventoryStatePurchased
    };

    AsemanStoreManager(QObject *parent = 0);
    ~AsemanStoreManager();

    void setPublicKey(const QString &pkey);
    QString publicKey() const;

    void setPackageName(const QString &name);
    QString packageName() const;

    void setBindIntent(const QString &path);
    QString bindIntent() const;

    void setCacheSource(const QString &path);
    QString cacheSource() const;

public slots:
    bool setup();

signals:
    void publicKeyChanged();
    void packageNameChanged();
    void bindIntentChanged();
    void cacheSourceChanged();

private slots:
    void inventoryStateChanged(const QString &sku, bool state);
    void propertyChanged();

private:
    void initProperties();
    void reinitCache();
    void initCore();

private:
    AsemanStoreManagerPrivate *p;
};

#endif // ASEMANSTOREMANAGER_H
