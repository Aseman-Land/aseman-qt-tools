/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANSTOREMANAGERMODEL_H
#define ASEMANSTOREMANAGERMODEL_H

#include "asemanabstractlistmodel.h"
#include "asemanstoremanager.h"

#include "asemantools_global.h"

class AsemanStoreManagerModelPrivate;
class LIBASEMANTOOLSSHARED_EXPORT AsemanStoreManagerModel : public AsemanAbstractListModel
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
    virtual ~AsemanStoreManagerModel();

    void setStoreManager(AsemanStoreManager *stm);
    AsemanStoreManager *storeManager() const;

    int id( const QModelIndex &index ) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    QHash<qint32,QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int count() const;

Q_SIGNALS:
    void storeManagerChanged();
    void countChanged();

private Q_SLOTS:
    void itemDetailsChanged();
    void inventoryStateChanged(const QString &sku);
    void changed(const QStringList &list);

private:
    AsemanStoreManagerModelPrivate *p;
};

#endif // ASEMANSTOREMANAGERMODEL_H
