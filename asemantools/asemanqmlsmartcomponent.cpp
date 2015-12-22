#include "asemanqmlsmartcomponent.h"

#include <QPointer>
#include <QDebug>
#include <QThread>
#include <QList>
#include <QEventLoop>
#include <QCoreApplication>

class AsemanQmlSmartComponentPrivate
{
public:
    QPointer<QQmlComponent> component;
    QUrl source;
};

AsemanQmlSmartComponent::AsemanQmlSmartComponent(QObject *parent) :
    QObject(parent)
{
    p = new AsemanQmlSmartComponentPrivate;
}

void AsemanQmlSmartComponent::setSource(const QUrl &url)
{
    if(p->source == url)
        return;

    p->source = url;
    if(p->component)
    {
        bool hadError = !p->component->errorString().isEmpty();
        p->component->deleteLater();
        p->component = 0;
        if(hadError)
            emit errorChanged();
    }

    if(p->source.isValid())
    {
        p->component = new QQmlComponent(qmlEngine(this), this);

        connect(p->component, SIGNAL(statusChanged(QQmlComponent::Status)),
                this, SLOT(statusChanged(QQmlComponent::Status)));

        p->component->loadUrl(p->source, QQmlComponent::Asynchronous);
    }

    emit sourceChanged();
}

QUrl AsemanQmlSmartComponent::source() const
{
    return p->source;
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

QObject *AsemanQmlSmartComponent::createObject(QObject *parent, const QVariantMap &data)
{
    if(status() == QQmlComponent::Null ||
       status() == QQmlComponent::Error )
        return 0;
    if(!p->component)
        return 0;

    while (p->component->isLoading())
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    if(!p->component->isReady())
        return 0;

    QObject *result = p->component->create(qmlContext(this));
    if(result)
    {
        result->setParent(parent);
        QMapIterator<QString,QVariant> i(data);
        while(i.hasNext())
        {
            i.next();
            result->setProperty(i.key().toUtf8(), i.value());
        }
    }

    return result;
}

void AsemanQmlSmartComponent::statusChanged(QQmlComponent::Status status)
{
    switch(static_cast<int>(status))
    {
    case QQmlComponent::Null:
        break;

    case QQmlComponent::Ready:
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

AsemanQmlSmartComponent::~AsemanQmlSmartComponent()
{
    delete p;
}

