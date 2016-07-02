#ifndef ASEMANCONTRIBUTORSMODEL_H
#define ASEMANCONTRIBUTORSMODEL_H

#include "asemanabstractlistmodel.h"
#include <QList>
#include <QUrl>

class AsemanContributorsModelItem;
class AsemanContributorsModelPrivate;
class AsemanContributorsModel : public AsemanAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ItemRoles)

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QList<QUrl> files READ files WRITE setFiles NOTIFY filesChanged)

public:
    enum ItemRoles {
        TextRole = Qt::UserRole,
        LinkRole,
        TypeRole
    };

    AsemanContributorsModel(QObject *parent = 0);
    ~AsemanContributorsModel();

    void setFiles(const QList<QUrl> & urls);
    QList<QUrl> files() const;

    int id( const QModelIndex &index ) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QHash<qint32,QByteArray> roleNames() const;

    int count() const;

public slots:
    void refresh();

signals:
    void countChanged();
    void filesChanged();

private:
    QList<AsemanContributorsModelItem> readData() const;

private:
    AsemanContributorsModelPrivate *p;
};

#endif // ASEMANCONTRIBUTORSMODEL_H
