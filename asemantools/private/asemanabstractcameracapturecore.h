#ifndef ASEMANABSTRACTCAMERACAPTURECORE_H
#define ASEMANABSTRACTCAMERACAPTURECORE_H

#include <QObject>

class AsemanAbstractCameraCaptureCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractCameraCaptureCore(QObject *parent = 0);
    ~AsemanAbstractCameraCaptureCore();

public slots:
    virtual int capture(const QString &dest) = 0;

signals:
    void imageCaptured(int id, const QString &path);
};

#endif // ASEMANABSTRACTCAMERACAPTURECORE_H
