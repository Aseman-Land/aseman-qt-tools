#ifndef ASEMANLOCATIONLISTENER_H
#define ASEMANLOCATIONLISTENER_H

#include <QObject>
#include <QGeoPositionInfo>

class AsemanLocationListenerPrivate;
class AsemanLocationListener : public QObject
{
    Q_OBJECT
public:
    AsemanLocationListener(QObject *parent = 0);
    ~AsemanLocationListener();

    void requestLocationUpdates(int interval);
    void getLastKnownLocation();

signals:
    void positionUpdated(const QGeoPositionInfo & update);

private:
    AsemanLocationListenerPrivate *p;
};

#endif // ASEMANLOCATIONLISTENER_H
