#ifndef ASEMANANDROIDLOCATIONLISTENERCORE_H
#define ASEMANANDROIDLOCATIONLISTENERCORE_H

#include "asemanabstractlocationlistenercore.h"
#include <QGeoPositionInfo>

class AsemanAndroidLocationListenerPrivate;
class AsemanAndroidLocationListenerCore : public AsemanAbstractLocationListenerCore
{
    Q_OBJECT
public:
    AsemanAndroidLocationListenerCore(QObject *parent = 0);
    ~AsemanAndroidLocationListenerCore();

    void requestLocationUpdates(int interval);
    void getLastKnownLocation();

private:
    AsemanAndroidLocationListenerPrivate *p;
};

Q_DECLARE_METATYPE(QGeoPositionInfo)

#endif // ASEMANANDROIDLOCATIONLISTENERCORE_H
