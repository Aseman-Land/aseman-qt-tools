#include "asemanandroidstoremangercore.h"

#include <QDebug>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QPointer>
#include <QString>

#include <jni.h>

QSet<AsemanAndroidStoreMangerCore*> store_manager_objects;

class AsemanAndroidStoreMangerCorePrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
    QSet<QString> inventories;
};

AsemanAndroidStoreMangerCore::AsemanAndroidStoreMangerCore() :
    AsemanAbstractStoreMangerCore()
{
    p = new AsemanAndroidStoreMangerCorePrivate;
    p->object = QAndroidJniObject("land/aseman/android/store/StoreManager");
    store_manager_objects.insert(this);
}

void AsemanAndroidStoreMangerCore::setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath)
{
    jstring jpkey = p->env->NewString(reinterpret_cast<const jchar*>(base64EncodedPublicKey.constData()), base64EncodedPublicKey.length());
    jstring jpack = p->env->NewString(reinterpret_cast<const jchar*>(storePackageName.constData()), storePackageName.length());
    jstring jintn = p->env->NewString(reinterpret_cast<const jchar*>(billingBindIntentPath.constData()), billingBindIntentPath.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", jpkey, jpack, jintn );
}

void AsemanAndroidStoreMangerCore::updateStates()
{
    p->object.callMethod<void>(__FUNCTION__, "()V");
}

bool AsemanAndroidStoreMangerCore::containsInventory(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    jboolean res = p->object.callMethod<jboolean>(__FUNCTION__, "(Ljava/lang/String;)Z", jsku );
    return res;
}

void AsemanAndroidStoreMangerCore::insertInventory(const QString &sku, bool state)
{
    p->inventories.insert(sku);
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;Z)V", jsku, state );
}

void AsemanAndroidStoreMangerCore::insertInventory(const QString &sku)
{
    p->inventories.insert(sku);
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;)V", jsku );
}

void AsemanAndroidStoreMangerCore::removeInventory(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;)V", jsku );
}

bool AsemanAndroidStoreMangerCore::getState(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    jboolean res = p->object.callMethod<jboolean>(__FUNCTION__, "(Ljava/lang/String;Z)Z", jsku );
    return res;
}

int AsemanAndroidStoreMangerCore::count()
{
    jboolean res = p->object.callMethod<jint>(__FUNCTION__, "()Z" );
    return res;
}

QStringList AsemanAndroidStoreMangerCore::inventories()
{
    return p->inventories.toList();
}

AsemanAndroidStoreMangerCore::~AsemanAndroidStoreMangerCore()
{
    store_manager_objects.remove(this);
    delete p;
}

static void inventoryStateChangedRecieved( JNIEnv *env, jobject obj ,jstring sku, jboolean state )
{
    Q_UNUSED(obj)
    jboolean a;
    const char *s = env->GetStringUTFChars(sku,&a);

    foreach( AsemanAndroidStoreMangerCore *smc, store_manager_objects )
        emit smc->inventoryStateChanged( QString(s), state );
}

static void setupFinishedRecieved( JNIEnv *env, jobject obj ,jboolean state )
{
    Q_UNUSED(obj)
    Q_UNUSED(env)
    foreach( AsemanAndroidStoreMangerCore *smc, store_manager_objects )
        emit smc->setupFinished(state);
}

bool aseman_str_mgr_registerNativeMethods() {
    JNINativeMethod methods[] {{"_inventoryStateChanged", "(Ljava/lang/String;Z)V", reinterpret_cast<void *>(inventoryStateChangedRecieved)},
                               {"_setupFinished", "(Z)V", reinterpret_cast<void *>(setupFinishedRecieved)}};

    QAndroidJniObject javaClass("land/aseman/android/store/StoreManager");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));

    env->DeleteLocalRef(objectClass);
    return true;
}

const bool aseman_str_mgr_native_methods_registered = aseman_str_mgr_registerNativeMethods();

