#ifndef ASEMANANDROIDCAMERACAPTURE_H
#define ASEMANANDROIDCAMERACAPTURE_H

#include "asemanabstractcameracapturecore.h"

class AsemanAndroidCameraCaptureCorePrivate;
class AsemanAndroidCameraCaptureCore : public AsemanAbstractCameraCaptureCore
{
    Q_OBJECT
public:
    AsemanAndroidCameraCaptureCore(QObject *parent = 0);
    ~AsemanAndroidCameraCaptureCore();

    int capture(const QString &dest);

private:
    AsemanAndroidCameraCaptureCorePrivate *p;
};

#endif // ASEMANANDROIDCAMERACAPTURE_H
