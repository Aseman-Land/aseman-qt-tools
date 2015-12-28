#ifndef ASEMANSTOREMANAGERMODEL_H
#define ASEMANSTOREMANAGERMODEL_H

#include "asemanabstractlistmodel.h"
#include "asemanstoremanager.h"

class AsemanStoreManagerModelPrivate;
class AsemanStoreManagerModel : public AsemanAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(AsemanStoreManager* storeManager READ storeManager WRITE setStoreManager NOTIFY storeManagerChanged)

public:
    enum DataRoles {
        InventoryIdRole = Qt::UserRole,
        PurchasedRole,
        PurchasingRole,
        InventoryPriceRole,
        InventoryTypeRole,
        InventoryTitleRole,
        InventoryDescriptionRole
    };

    AsemanStoreManagerModel(QObject *parent = 0);
    ~AsemanStoreManagerModel();

    void setStoreManager(AsemanStoreManager *stm);
    AsemanStoreManager *storeManager() const;

    int id( const QModelIndex &index ) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    QHash<qint32,QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int count() const;

signals:
    void storeManagerChanged();
    void countChanged();

private slots:
    void itemDetailsChanged();
    void changed(const QStringList &list);

private:
    AsemanStoreManagerModelPrivate *p;
};

#endif // ASEMANSTOREMANAGERMODEL_H
