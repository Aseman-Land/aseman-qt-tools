#ifndef ASEMANSTOREMANAGER_H
#define ASEMANSTOREMANAGER_H

#include <QObject>

class AsemanStoreManagerPrivate;
class AsemanStoreManager : public QObject
{
    Q_OBJECT
public:
    AsemanStoreManager(QObject *parent = 0);
    ~AsemanStoreManager();

private:
    AsemanStoreManagerPrivate *p;
};

#endif // ASEMANSTOREMANAGER_H
