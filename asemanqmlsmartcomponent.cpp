#include "asemanqmlsmartcomponent.h"

#include <QPointer>
#include <QDebug>
#include <QThread>
#include <QList>
#include <QEventLoop>
#include <QCoreApplication>
#include <QTimerEvent>

class AsemanQmlSmartComponentPrivate
{
public:
    QPointer<QQmlComponent> component;
    QUrl source;
    int createTimer;
    int delayInterval;
};

AsemanQmlSmartComponent::AsemanQmlSmartComponent(QObject *parent) :
    QObject(parent)
{
    p = new AsemanQmlSmartComponentPrivate;
    p->createTimer = 0;
    p->delayInterval = 1;
}

void AsemanQmlSmartComponent::setSource(const QUrl &url)
{
    if(p->source == url)
        return;

    if(p->component)
    {
        bool hadError = !p->component->errorString().isEmpty();
        p->component->deleteLater();
        p->component = 0;
        if(hadError)
            emit errorChanged();
    }

    p->source = url;
    recheckTimer();

    emit sourceChanged();
}

QUrl AsemanQmlSmartComponent::source() const
{
    return p->source;
}

void AsemanQmlSmartComponent::setDelayInterval(int ms)
{
    if(p->delayInterval == ms)
        return;

    p->delayInterval = ms;
    recheckTimer();
    emit delayIntervalChanged();
}

int AsemanQmlSmartComponent::delayInterval() const
{
    return p->delayInterval;
}

int AsemanQmlSmartComponent::status() const
{
    if(p->component)
        return p->component->status();
    else
        return QQmlComponent::Null;
}

QString AsemanQmlSmartComponent::error() const
{
    if(p->component)
        return p->component->errorString();
    else
        return QString();
}

QQmlComponent *AsemanQmlSmartComponent::component() const
{
    if(p->component && p->component->isReady())
        return p->component;
    else
        return 0;
}

void AsemanQmlSmartComponent::statusChanged(QQmlComponent::Status status)
{
    switch(static_cast<int>(status))
    {
    case QQmlComponent::Null:
        break;

    case QQmlComponent::Ready:
        emit componentChanged();
        emit ready();
        break;

    case QQmlComponent::Loading:
        break;

    case QQmlComponent::Error:
        qDebug() << error();
        emit errorChanged();
        break;
    }

    emit statusChanged();
}

void AsemanQmlSmartComponent::recheckTimer()
{
    if(p->createTimer)
        killTimer(p->createTimer);
    if(p->delayInterval == -1)
        return;
    if(p->source.isValid())
        p->createTimer = startTimer(p->delayInterval);
}

void AsemanQmlSmartComponent::createComponent()
{
    if(!p->source.isValid())
        return;

    p->component = new QQmlComponent(qmlEngine(this), this);
    connect(p->component, SIGNAL(statusChanged(QQmlComponent::Status)),
            this, SLOT(statusChanged(QQmlComponent::Status)));

    p->component->loadUrl(p->source, QQmlComponent::Asynchronous);
}

void AsemanQmlSmartComponent::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == p->createTimer)
    {
        createComponent();
        killTimer(p->createTimer);
        p->createTimer = 0;
    }
}

AsemanQmlSmartComponent::~AsemanQmlSmartComponent()
{
    delete p;
}

