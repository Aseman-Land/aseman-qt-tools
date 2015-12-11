#include "asemanandroidstoremanagercore.h"

#include <QDebug>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QPointer>
#include <QString>

#include <jni.h>

QSet<AsemanAndroidStoreManagerCore*> store_manager_objects;

class AsemanAndroidStoreManagerCorePrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
    QSet<QString> inventories;
};

AsemanAndroidStoreManagerCore::AsemanAndroidStoreManagerCore() :
    AsemanAbstractStoreManagerCore()
{
    p = new AsemanAndroidStoreManagerCorePrivate;
    p->object = QAndroidJniObject("land/aseman/android/store/StoreManager");
    store_manager_objects.insert(this);
}

void AsemanAndroidStoreManagerCore::setup(const QString &base64EncodedPublicKey, const QString &storePackageName, const QString &billingBindIntentPath)
{
    jstring jpkey = p->env->NewString(reinterpret_cast<const jchar*>(base64EncodedPublicKey.constData()), base64EncodedPublicKey.length());
    jstring jpack = p->env->NewString(reinterpret_cast<const jchar*>(storePackageName.constData()), storePackageName.length());
    jstring jintn = p->env->NewString(reinterpret_cast<const jchar*>(billingBindIntentPath.constData()), billingBindIntentPath.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", jpkey, jpack, jintn );
}

void AsemanAndroidStoreManagerCore::updateStates()
{
    p->object.callMethod<void>(__FUNCTION__, "()V");
}

bool AsemanAndroidStoreManagerCore::containsInventory(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    jboolean res = p->object.callMethod<jboolean>(__FUNCTION__, "(Ljava/lang/String;)Z", jsku );
    return res;
}

void AsemanAndroidStoreManagerCore::insertInventory(const QString &sku, bool state)
{
    p->inventories.insert(sku);
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;Z)V", jsku, state );
}

void AsemanAndroidStoreManagerCore::insertInventory(const QString &sku)
{
    p->inventories.insert(sku);
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;)V", jsku );
}

void AsemanAndroidStoreManagerCore::removeInventory(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;)V", jsku );
}

bool AsemanAndroidStoreManagerCore::getState(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    jboolean res = p->object.callMethod<jboolean>(__FUNCTION__, "(Ljava/lang/String;Z)Z", jsku );
    return res;
}

int AsemanAndroidStoreManagerCore::count()
{
    jboolean res = p->object.callMethod<jint>(__FUNCTION__, "()Z" );
    return res;
}

void AsemanAndroidStoreManagerCore::clear()
{
    p->object.callMethod<void>(__FUNCTION__, "()V" );
}

void AsemanAndroidStoreManagerCore::purchaseInventory(const QString &sku)
{
    jstring jsku = p->env->NewString(reinterpret_cast<const jchar*>(sku.constData()), sku.length());
    p->object.callMethod<void>(__FUNCTION__, "(Ljava/lang/String;)V", jsku );
}

QStringList AsemanAndroidStoreManagerCore::inventories()
{
    return p->inventories.toList();
}

AsemanAndroidStoreManagerCore::~AsemanAndroidStoreManagerCore()
{
    store_manager_objects.remove(this);
    delete p;
}

static void inventoryStateChangedRecieved( JNIEnv *env, jobject obj ,jstring sku, jboolean state )
{
    Q_UNUSED(obj)
    jboolean a;
    const char *s = env->GetStringUTFChars(sku,&a);

    foreach( AsemanAndroidStoreManagerCore *smc, store_manager_objects )
        emit smc->inventoryStateChanged( QString(s), state );
}

static void setupFinishedRecieved( JNIEnv *env, jobject obj ,jboolean state )
{
    Q_UNUSED(obj)
    Q_UNUSED(env)
    foreach( AsemanAndroidStoreManagerCore *smc, store_manager_objects )
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

