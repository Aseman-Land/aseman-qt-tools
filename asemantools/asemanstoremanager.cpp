#include "asemanstoremanager.h"
#include "private/asemanabstractstoremangercore.h"

#include <QPointer>

#ifdef Q_OS_ANDROID
#include "private/asemanandroidstoremangercore.h"
typedef AsemanAndroidStoreMangerCore AsemanStoreMangerCore;
#else
typedef AsemanNullStoreMangerCore AsemanStoreMangerCore;
#endif

QPointer<AsemanAbstractStoreMangerCore> aseman_store_manager_core;

class AsemanStoreManagerPrivate
{
public:
};

AsemanStoreManager::AsemanStoreManager(QObject *parent) :
    QObject(parent)
{
    p = new AsemanStoreManagerPrivate;

    if(!aseman_store_manager_core)
        aseman_store_manager_core = new AsemanStoreMangerCore();
}

AsemanStoreManager::~AsemanStoreManager()
{
    delete p;
}

