#ifndef ASEMANABSTRACTLOCATIONLISTENERCORE_H
#define ASEMANABSTRACTLOCATIONLISTENERCORE_H

#include <QObject>
#include <QGeoPositionInfo>

class AsemanAbstractLocationListenerCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractLocationListenerCore(QObject *parent = 0);
    ~AsemanAbstractLocationListenerCore();

    virtual void requestLocationUpdates(int interval) = 0;
    virtual void getLastKnownLocation();
    virtual void stop();

signals:
    void positionUpdated(const QGeoPositionInfo & update);

private slots:
    void updated(const QGeoPositionInfo & update);

private:
    QGeoPositionInfo _lastLocation;
};

#endif // ASEMANABSTRACTLOCATIONLISTENERCORE_H
