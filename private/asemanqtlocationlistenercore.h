#ifndef ASEMANQTLOCATIONLISTENERCORE_H
#define ASEMANQTLOCATIONLISTENERCORE_H

#include "asemanabstractlocationlistenercore.h"

class AsemanQtLocationListenerCorePrivate;
class AsemanQtLocationListenerCore: public AsemanAbstractLocationListenerCore
{
public:
    AsemanQtLocationListenerCore(QObject *parent = 0);
    ~AsemanQtLocationListenerCore();

    void requestLocationUpdates(int interval);
    void stop();

private:
    AsemanQtLocationListenerCorePrivate *p;
};

#endif // ASEMANQTLOCATIONLISTENERCORE_H
