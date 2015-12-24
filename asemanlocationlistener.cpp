#include "asemanlocationlistener.h"

#ifdef Q_OS_ANDROID
#include "private/asemanandroidlocationlistenercore.h"
typedef AsemanAndroidLocationListenerCore LocationListenerCore;
#else
#include "private/asemanqtlocationlistenercore.h"
typedef AsemanQtLocationListenerCore LocationListenerCore;
#endif

class AsemanLocationListenerPrivate
{
public:
    AsemanAbstractLocationListenerCore *core;
};

AsemanLocationListener::AsemanLocationListener(QObject *parent) :
    QObject(parent)
{
    p = new AsemanLocationListenerPrivate;
    p->core = new LocationListenerCore(this);

    connect(p->core, SIGNAL(positionUpdated(QGeoPositionInfo)),
            SIGNAL(positionUpdated(QGeoPositionInfo)), Qt::QueuedConnection);
}

void AsemanLocationListener::requestLocationUpdates(int interval)
{
    p->core->requestLocationUpdates(interval);
}

void AsemanLocationListener::getLastKnownLocation()
{
    p->core->getLastKnownLocation();
}

AsemanLocationListener::~AsemanLocationListener()
{
    p->core->stop();
    delete p;
}

