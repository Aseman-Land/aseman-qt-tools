#include "asemanqmlengine.h"
#include "asemanqttools.h"

class AsemanQmlEnginePrivate
{
public:
};

AsemanQmlEngine::AsemanQmlEngine(QObject *parent) :
    QQmlApplicationEngine(parent)
{
    p = new AsemanQmlEnginePrivate;

#ifndef ASEMAN_QML_PLUGIN
    AsemanQtTools::safeRegisterTypes("AsemanTools", this);
#endif
}

AsemanQmlEngine::~AsemanQmlEngine()
{
    delete p;
}
