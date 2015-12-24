#include "asemanabstractlocationlistenercore.h"

AsemanAbstractLocationListenerCore::AsemanAbstractLocationListenerCore(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(positionUpdated(QGeoPositionInfo)), SLOT(updated(QGeoPositionInfo)));
}

void AsemanAbstractLocationListenerCore::getLastKnownLocation()
{
    emit positionUpdated(_lastLocation);
}

void AsemanAbstractLocationListenerCore::stop()
{
    requestLocationUpdates(-1);
}

void AsemanAbstractLocationListenerCore::updated(const QGeoPositionInfo &update)
{
    if(!update.isValid())
        return;

    _lastLocation = update;
}

AsemanAbstractLocationListenerCore::~AsemanAbstractLocationListenerCore()
{

}

