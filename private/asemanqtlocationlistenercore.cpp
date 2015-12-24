#include "asemanqtlocationlistenercore.h"

#include <QGeoPositionInfoSource>

class AsemanQtLocationListenerCorePrivate
{
public:
    QGeoPositionInfoSource *source;
};

AsemanQtLocationListenerCore::AsemanQtLocationListenerCore(QObject *parent) :
    AsemanAbstractLocationListenerCore(parent)
{
    p = new AsemanQtLocationListenerCorePrivate;
    p->source = QGeoPositionInfoSource::createDefaultSource(this);
    connect(p->source, SIGNAL(positionUpdated(QGeoPositionInfo)), SIGNAL(positionUpdated(QGeoPositionInfo)));
}

void AsemanQtLocationListenerCore::requestLocationUpdates(int interval)
{
    p->source->requestUpdate(interval);
}

void AsemanQtLocationListenerCore::stop()
{
    p->source->stopUpdates();
}

AsemanQtLocationListenerCore::~AsemanQtLocationListenerCore()
{
    delete p;
}

