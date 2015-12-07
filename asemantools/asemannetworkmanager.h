#ifndef ASEMANNETWORKMANAGER_H
#define ASEMANNETWORKMANAGER_H

#include <QObject>
#include <QNetworkConfiguration>
#include <QVariantMap>

class AsemanNetworkManagerItem;
class AsemanNetworkCheckerPrivate;
class AsemanNetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString defaultNetworkIdentifier READ defaultNetworkIdentifier NOTIFY defaultNetworkIdentifierChanged)
    Q_PROPERTY(QVariantMap configurations READ configurations NOTIFY configurationsChanged)
    Q_PROPERTY(AsemanNetworkManagerItem* defaultNetwork READ defaultNetwork NOTIFY defaultNetworkChanged)

public:
    AsemanNetworkManager(QObject *parent = 0);
    ~AsemanNetworkManager();

    QString defaultNetworkIdentifier() const;
    AsemanNetworkManagerItem *defaultNetwork() const;
    QVariantMap configurations() const;

signals:
    void defaultNetworkIdentifierChanged();
    void defaultNetworkChanged();
    void configurationsChanged();

private slots:
    void configureChanged(const QNetworkConfiguration &config);
    void configureAdded(const QNetworkConfiguration &config);
    void configureRemoved(const QNetworkConfiguration &config);
    void updateCheck();

private:
    AsemanNetworkCheckerPrivate *p;
};

#endif // ASEMANNETWORKMANAGER_H
