#include "asemanandroidstoremanagercore.h"
#include "../asemanstoremanager.h"

#include <QDebug>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QPointer>
#include <QString>

#include <jni.h>

QHash<jobject, AsemanAndroidStoreManagerCore*> store_manager_objects;

AsemanAndroidStoreManagerCore *getStoreManagerObject(jobject obj)
{
    QHashIterator<jobject, AsemanAndroidStoreManagerCore*> i(store_manager_objects);
    while(i.hasNext())
    {
        i.next();
        if(QAndroidJniObject(i.key()) == QAndroidJniObject(obj))
            return i.value();
    }

    return 0;
}

class AsemanAndroidStoreManagerCorePrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
    QSet<QString> inventories;
    QMap<QString, AsemanStoreManagerInventoryItem> details;
};

AsemanAndroidStoreManagerCore::AsemanAndroidStoreManagerCore() :
    AsemanAbstractStoreManagerCore()
{
    p = new AsemanAndroidStoreManagerCorePrivate;
    p->object = QAndroidJniObject("land/aseman/android/store/StoreManager");
    store_manager_objects.insert(p->object.object<jobject>(), this);
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
    jint res = p->object.callMethod<jint>(__FUNCTION__, "()I" );
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

QMap<QString,AsemanStoreManagerInventoryItem> AsemanAndroidStoreManagerCore::itemDetails() const
{
    return p->details;
}

void AsemanAndroidStoreManagerCore::detailsFetched(const QString &sku, const QString &type, const QString &price, const QString &title, const QString &description)
{
    AsemanStoreManagerInventoryItem item;
    item.sku = sku;
    item.type = type;
    item.price = price;
    item.title = title;
    item.description = description;

    p->details[sku] = item;
    emit itemDetailsChanged();
}

AsemanAndroidStoreManagerCore::~AsemanAndroidStoreManagerCore()
{
    p->object.callMethod<void>("end", "()V" );
    store_manager_objects.remove(p->object.object<jobject>());
    delete p;
}

static void detailsFetched(JNIEnv *env, jobject obj ,jstring sku, jstring type, jstring price, jstring title, jstring description)
{
    AsemanAndroidStoreManagerCore *smc = getStoreManagerObject(obj);
    if(!smc)
        return;

    jboolean a;
    QString qsku = env->GetStringUTFChars(sku,&a);
    QString qtype = env->GetStringUTFChars(type,&a);
    QString qprice = env->GetStringUTFChars(price,&a);
    QString qtitle = env->GetStringUTFChars(title,&a);
    QString qdesc = env->GetStringUTFChars(description,&a);

    QMetaObject::invokeMethod(smc, "detailsFetched", Q_ARG(QString, qsku)
                              , Q_ARG(QString, qtype), Q_ARG(QString, qprice)
                              , Q_ARG(QString, qtitle), Q_ARG(QString, qdesc));
}

static void inventoryStateChangedRecieved( JNIEnv *env, jobject obj ,jstring sku, jboolean state )
{
    AsemanAndroidStoreManagerCore *smc = getStoreManagerObject(obj);
    if(!smc)
        return;

    jboolean a;
    QString qsku = env->GetStringUTFChars(sku,&a);
    bool cstate = state;
    QMetaObject::invokeMethod(smc, "inventoryStateChanged", Q_ARG(QString, qsku), Q_ARG(bool,cstate));
}

static void setupFinishedRecieved( JNIEnv *env, jobject obj ,jboolean state )
{
    Q_UNUSED(env)
    AsemanAndroidStoreManagerCore *smc = getStoreManagerObject(obj);
    if(!smc)
        return;

    bool cstate = state;
    QMetaObject::invokeMethod(smc, "setupFinished", Q_ARG(bool, cstate));
}

bool aseman_str_mgr_registerNativeMethods() {
    JNINativeMethod methods[] {{"_inventoryStateChanged", "(Ljava/lang/String;Z)V", reinterpret_cast<void *>(inventoryStateChangedRecieved)},
                               {"_detailsFetched", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", reinterpret_cast<void *>(detailsFetched)},
                               {"_setupFinished", "(Z)V", reinterpret_cast<void *>(setupFinishedRecieved)}};

    QAndroidJniObject javaClass("land/aseman/android/store/StoreManager");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));

    env->DeleteLocalRef(objectClass);
    return true;
}

const bool aseman_str_mgr_native_methods_registered = aseman_str_mgr_registerNativeMethods();

