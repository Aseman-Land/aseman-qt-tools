#ifndef ASEMANABSTRACTCAMERACAPTURECORE_H
#define ASEMANABSTRACTCAMERACAPTURECORE_H

#include <QObject>
#include "../asemancameracapture.h"

class AsemanAbstractCameraCaptureCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractCameraCaptureCore(QObject *parent = 0);
    ~AsemanAbstractCameraCaptureCore();

    virtual int capture(const QString &dest, AsemanCameraCapture::CameraFace face) = 0;

signals:
    void imageCaptured(int id, const QString &path);
};

#endif // ASEMANABSTRACTCAMERACAPTURECORE_H
