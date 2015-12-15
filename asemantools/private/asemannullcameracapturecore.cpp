#include "asemannullcameracapturecore.h"

AsemanNullCameraCaptureCore::AsemanNullCameraCaptureCore(QObject *parent) :
    AsemanAbstractCameraCaptureCore(parent)
{

}

int AsemanNullCameraCaptureCore::capture(const QString &dest, AsemanCameraCapture::CameraFace face)
{
    Q_UNUSED(face)
    emit imageCaptured(0, dest);
    return 0;
}

AsemanNullCameraCaptureCore::~AsemanNullCameraCaptureCore()
{

}

