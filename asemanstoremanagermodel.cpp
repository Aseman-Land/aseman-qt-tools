#include "asemanstoremanagermodel.h"

#include <QPointer>
#include <QMetaObject>
#include <QMetaProperty>

class AsemanStoreManagerModelPrivate
{
public:
    QPointer<AsemanStoreManager> store;
    QStringList list;
};

AsemanStoreManagerModel::AsemanStoreManagerModel(QObject *parent) :
    AsemanAbstractListModel(parent)
{
    p = new AsemanStoreManagerModelPrivate;
}

void AsemanStoreManagerModel::setStoreManager(AsemanStoreManager *store)
{
    if(p->store == store)
        return;

    if(p->store)
        disconnect(p->store, SIGNAL(itemDetailsChanged()), this, SLOT(itemDetailsChanged()));

    p->store = store;
    if(p->store)
        connect(p->store, SIGNAL(itemDetailsChanged()), this, SLOT(itemDetailsChanged()));

    itemDetailsChanged();
    emit storeManagerChanged();
}

AsemanStoreManager *AsemanStoreManagerModel::storeManager() const
{
    return p->store;
}

int AsemanStoreManagerModel::id(const QModelIndex &index) const
{
    return index.row();
}

int AsemanStoreManagerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count();
}

QVariant AsemanStoreManagerModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if(!p->store)
        return result;

    const int id = AsemanStoreManagerModel::id(index);
    const QString sku = p->list.at(id);

    switch(role)
    {
    case InventoryIdRole:
        result = sku;
        break;
    case PurchasedRole:
        result = (p->store->inventoryState(sku) == AsemanStoreManager::InventoryStatePurchased);
        break;
    case PurchasingRole:
        result = (p->store->inventoryState(sku) == AsemanStoreManager::InventoryStatePurchasing);
        break;
    case InventoryPriceRole:
        result = p->store->itemDetails()[sku].price;
        break;
    case InventoryTypeRole:
        result = p->store->itemDetails()[sku].type;
        break;
    case InventoryTitleRole:
        result = p->store->itemDetails()[sku].title;
        break;
    case InventoryDescriptionRole:
        result = p->store->itemDetails()[sku].description;
        break;
    }

    return result;
}

bool AsemanStoreManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    if(!p->store)
        return result;

    const int id = AsemanStoreManagerModel::id(index);
    const QString sku = p->list.at(id);

    switch(role)
    {
    case PurchasingRole:
        if(value.toBool())
            result = p->store->startPurchasing(sku);
        break;

    case PurchasedRole:
    case InventoryIdRole:
    case InventoryPriceRole:
    case InventoryTypeRole:
    case InventoryTitleRole:
    case InventoryDescriptionRole:
        break;
    }

    return result;
}

QHash<qint32, QByteArray> AsemanStoreManagerModel::roleNames() const
{
    static QHash<qint32, QByteArray> *res = 0;
    if( res )
        return *res;

    res = new QHash<qint32, QByteArray>();
    res->insert( InventoryIdRole, "sku");
    res->insert( PurchasedRole, "purchased");
    res->insert( PurchasingRole, "purchasing");
    res->insert( InventoryPriceRole, "price");
    res->insert( InventoryTypeRole, "type");
    res->insert( InventoryTitleRole, "title");
    res->insert( InventoryDescriptionRole, "description");

    return *res;
}

Qt::ItemFlags AsemanStoreManagerModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

int AsemanStoreManagerModel::count() const
{
    return p->list.count();
}

void AsemanStoreManagerModel::itemDetailsChanged()
{
    if(p->store)
    {
        QStringList list;
        QStringList keys = p->store->itemDetails().keys();

        const QMetaObject *meta = p->store->metaObject();
        for(int i=0; i<meta->propertyCount(); i++)
        {
            const QString &name = meta->property(i).name();
            if(!keys.contains(name))
                continue;

            list << name;
        }
        changed(list);
    }
    else
    {
        changed(QStringList());
    }
}

void AsemanStoreManagerModel::changed(const QStringList &list)
{
    bool count_changed = (list.count()==p->list.count());

    for( int i=0 ; i<p->list.count() ; i++ )
    {
        const QString &item = p->list.at(i);
        if( list.contains(item) )
            continue;

        beginRemoveRows(QModelIndex(), i, i);
        p->list.removeAt(i);
        i--;
        endRemoveRows();
    }

    QList<QString> temp_list = list;
    for( int i=0 ; i<temp_list.count() ; i++ )
    {
        const QString &item = temp_list.at(i);
        if( p->list.contains(item) )
            continue;

        temp_list.removeAt(i);
        i--;
    }
    while( p->list != temp_list )
        for( int i=0 ; i<p->list.count() ; i++ )
        {
            const QString &item = p->list.at(i);
            int nw = temp_list.indexOf(item);
            if( i == nw )
                continue;

            beginMoveRows( QModelIndex(), i, i, QModelIndex(), nw>i?nw+1:nw );
            p->list.move( i, nw );
            endMoveRows();
        }

    for( int i=0 ; i<list.count() ; i++ )
    {
        const QString &item = list.at(i);
        if( p->list.contains(item) )
            continue;

        beginInsertRows(QModelIndex(), i, i );
        p->list.insert( i, item );
        endInsertRows();
    }

    if(count_changed)
        emit countChanged();
}

AsemanStoreManagerModel::~AsemanStoreManagerModel()
{
    delete p;
}

