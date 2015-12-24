#ifndef ASEMANCAMERACAPTURE_H
#define ASEMANCAMERACAPTURE_H

#include <QObject>

class AsemanCameraCapturePrivate;
class AsemanCameraCapture : public QObject
{
    Q_OBJECT
public:
    enum CameraFace {
        CameraFacingFront,
        CameraFacingBack
    };

    AsemanCameraCapture(QObject *parent = 0);
    ~AsemanCameraCapture();

public slots:
    int capture(const QString &dest, AsemanCameraCapture::CameraFace face);

signals:
    void imageCaptured(int id, const QString &path);

private:
    AsemanCameraCapturePrivate *p;
};

#endif // ASEMANCAMERACAPTURE_H
