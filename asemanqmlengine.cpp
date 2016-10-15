#include "asemanqmlengine.h"
#include "asemanqttools.h"

#include <QDebug>

class AsemanQmlEnginePrivate
{
public:
};

AsemanQmlEngine::AsemanQmlEngine(QObject *parent) :
    QQmlApplicationEngine(parent)
{
    p = new AsemanQmlEnginePrivate;

#ifndef ASEMAN_QML_PLUGIN
    if(!AsemanQtTools::safeRegisterTypes("AsemanTools", this))
        qDebug() << "Register AsemanTools failed! using system AsemanTools instead...";
#endif
}

AsemanQmlEngine::~AsemanQmlEngine()
{
    delete p;
}
