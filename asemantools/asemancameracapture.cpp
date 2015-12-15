#include "asemancameracapture.h"

#ifdef Q_OS_ANDROID
#include "private/asemanandroidcameracapturecore.h"
typedef AsemanAndroidCameraCaptureCore CameraCaptureCore;
#else
#include "private/asemannullcameracapturecore.h"
typedef AsemanNullCameraCaptureCore CameraCaptureCore;
#endif

class AsemanCameraCapturePrivate
{
public:
    AsemanAbstractCameraCaptureCore *core;
};

AsemanCameraCapture::AsemanCameraCapture(QObject *parent) :
    QObject(parent)
{
    p = new AsemanCameraCapturePrivate;
    p->core = new CameraCaptureCore(this);

    connect(p->core, SIGNAL(imageCaptured(int,QString)),
            SIGNAL(imageCaptured(int,QString)), Qt::QueuedConnection);
}

int AsemanCameraCapture::capture(const QString &dest, AsemanCameraCapture::CameraFace face)
{
    return p->core->capture(dest, face);
}

AsemanCameraCapture::~AsemanCameraCapture()
{
    delete p;
}

