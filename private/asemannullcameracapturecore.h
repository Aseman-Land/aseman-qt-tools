#ifndef ASEMANNULLCAMERACAPTURECORE_H
#define ASEMANNULLCAMERACAPTURECORE_H

#include "asemanabstractcameracapturecore.h"

class AsemanNullCameraCaptureCore : public AsemanAbstractCameraCaptureCore
{
    Q_OBJECT
public:
    AsemanNullCameraCaptureCore(QObject *parent = 0);
    ~AsemanNullCameraCaptureCore();

    int capture(const QString &dest, AsemanCameraCapture::CameraFace face);
};

#endif // ASEMANNULLCAMERACAPTURECORE_H
