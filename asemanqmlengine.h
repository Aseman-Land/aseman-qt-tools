#ifndef ASEMANQMLENGINE_H
#define ASEMANQMLENGINE_H

#include <QQmlApplicationEngine>

class AsemanQmlEnginePrivate;
class AsemanQmlEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    AsemanQmlEngine(QObject *parent = 0);
    ~AsemanQmlEngine();

signals:

public slots:

private:
    AsemanQmlEnginePrivate *p;
};

#endif // ASEMANQMLENGINE_H
