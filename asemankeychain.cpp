#include "asemankeychain.h"
#include "asemankdewallet.h"

#include <qt5keychain/keychain.h>

#include <QDebug>
#include <QEventLoop>
#include <QtQml>

#include <functional>

using namespace QKeychain;

class AsemanKeychainPrivate
{
public:
    QString service;
};

AsemanKeychain::AsemanKeychain(QObject *parent) :
    QObject(parent)
{
    p = new AsemanKeychainPrivate;
}

void AsemanKeychain::setService(const QString &service)
{
    if(p->service == service)
        return;

    p->service = service;
    emit serviceChanged();
}

QString AsemanKeychain::service() const
{
    return p->service;
}

QString AsemanKeychain::read(const QString &key, const QJSValue &jsCallback)
{
    ReadPasswordJob *job = new ReadPasswordJob(p->service);
    job->setAutoDelete(true);
    job->setKey(key);

    QQmlEngine *engine = qmlEngine(this);
    const bool hasCallback = (jsCallback.isCallable() && !jsCallback.isNull() && engine);

    if(hasCallback)
    {
        job->connect(job, &ReadPasswordJob::finished, this, [this, engine, job, jsCallback](QKeychain::Job*){
            const QString pw = job->textData();
            if(job->error())
                qDebug() << "Restoring password failed: " << qPrintable(job->errorString());

            QJSValue(jsCallback).call( QJSValueList()<<pw );
        });
        job->start();
        return QString();
    }
    else
    {
        QEventLoop loop;
        job->connect(job, &ReadPasswordJob::finished, &loop, &QEventLoop::quit );
        job->start();
        loop.exec();

        const QString pw = job->textData();
        if(job->error())
            qDebug() << "Restoring password failed: " << qPrintable(job->errorString());
        return pw;
    }
}

QByteArray AsemanKeychain::readData(const QString &key, const QJSValue &jsCallback)
{
    ReadPasswordJob *job = new ReadPasswordJob(p->service);
    job->setAutoDelete(true);
    job->setKey(key);

    QQmlEngine *engine = qmlEngine(this);
    const bool hasCallback = (jsCallback.isCallable() && !jsCallback.isNull() && engine);

    if(hasCallback)
    {
        job->connect(job, &ReadPasswordJob::finished, this, [this, engine, job, jsCallback](QKeychain::Job*){
            const QByteArray pw = job->binaryData();
            if(job->error())
                qDebug() << "Restoring password failed: " << qPrintable(job->errorString());

            QJSValue(jsCallback).call( QJSValueList()<<engine->toScriptValue<QByteArray>(pw) );
        });
        job->start();
        return QByteArray();
    }
    else
    {
        QEventLoop loop;
        job->connect(job, &ReadPasswordJob::finished, &loop, &QEventLoop::quit );
        job->start();
        loop.exec();

        const QByteArray pw = job->binaryData();
        if(job->error())
            qDebug() << "Restoring password failed: " << qPrintable(job->errorString());
        return pw;
    }
}

bool AsemanKeychain::write(const QString &key, const QString &data, const QJSValue &jsCallback)
{
    WritePasswordJob *job = new WritePasswordJob(p->service);
    job->setAutoDelete(true);
    job->setKey(key);
    job->setTextData(data);

    QQmlEngine *engine = qmlEngine(this);
    const bool hasCallback = (jsCallback.isCallable() && !jsCallback.isNull() && engine);

    if(hasCallback)
    {
        job->connect(job, &WritePasswordJob::finished, this, [this, engine, job, jsCallback](QKeychain::Job*){
            if(job->error())
                qDebug() << "Writting password failed: " << qPrintable(job->errorString());

            QJSValue(jsCallback).call( QJSValueList()<<!job->error() );
        });
        job->start();
        return true;
    }
    else
    {
        QEventLoop loop;
        job->connect(job, &WritePasswordJob::finished, &loop, &QEventLoop::quit );
        job->start();
        loop.exec();

        if(job->error())
            qDebug() << "Writting password failed: " << qPrintable(job->errorString());
        return !job->error();
    }
}

bool AsemanKeychain::writeData(const QString &key, const QByteArray &data, const QJSValue &jsCallback)
{
    WritePasswordJob *job = new WritePasswordJob(p->service);
    job->setAutoDelete(true);
    job->setKey(key);
    job->setBinaryData(data);

    QQmlEngine *engine = qmlEngine(this);
    const bool hasCallback = (jsCallback.isCallable() && !jsCallback.isNull() && engine);

    if(hasCallback)
    {
        job->connect(job, &WritePasswordJob::finished, this, [this, engine, job, jsCallback](QKeychain::Job*){
            if(job->error())
                qDebug() << "Writting password failed: " << qPrintable(job->errorString());

            QJSValue(jsCallback).call( QJSValueList()<<!job->error() );
        });
        job->start();
        return true;
    }
    else
    {
        QEventLoop loop;
        job->connect(job, &WritePasswordJob::finished, &loop, &QEventLoop::quit );
        job->start();
        loop.exec();

        if(job->error())
            qDebug() << "Writting password failed: " << qPrintable(job->errorString());
        return !job->error();
    }
}

bool AsemanKeychain::remove(const QString &key, const QJSValue &jsCallback)
{
    DeletePasswordJob *job = new DeletePasswordJob(p->service);
    job->setAutoDelete(true);
    job->setKey(key);

    QQmlEngine *engine = qmlEngine(this);
    const bool hasCallback = (jsCallback.isCallable() && !jsCallback.isNull() && engine);

    if(hasCallback)
    {
        job->connect(job, &DeletePasswordJob::finished, this, [this, engine, job, jsCallback](QKeychain::Job*){
            if(job->error())
                qDebug() << "Delete password failed: " << qPrintable(job->errorString());

            QJSValue(jsCallback).call( QJSValueList()<<!job->error() );
        });
        job->start();
        return true;
    }
    else
    {
        QEventLoop loop;
        job->connect(job, &DeletePasswordJob::finished, &loop, &QEventLoop::quit );
        job->start();
        loop.exec();

        if(job->error())
            qDebug() << "Delete password failed: " << qPrintable(job->errorString());
        return !job->error();
    }
}

AsemanKeychain::~AsemanKeychain()
{
    delete p;
}
