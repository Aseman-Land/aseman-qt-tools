#define PROPERTY_KEY(PROPERTY) QString(p->caregory.isEmpty()? PROPERTY : p->caregory+"/"+PROPERTY)

#include "asemansettings.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QDir>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

class AsemanSettingsPrivate
{
public:
    QHash<QByteArray, QByteArray> signalsProperties;
    QSettings *settings;
    QString caregory;
    QString source;
};

AsemanSettings::AsemanSettings(QObject *parent) : QObject(parent)
{
    p = new AsemanSettingsPrivate;
    p->settings = 0;

    initProperties();
}

void AsemanSettings::setCategory(const QString &category)
{
    if(p->caregory == category)
        return;

    p->caregory = category;
    initProperties();
    emit categoryChanged();
}

QString AsemanSettings::category() const
{
    return p->caregory;
}

void AsemanSettings::setSource(const QString &source)
{
    if(p->source == source)
        return;

    p->source = source;
    if(p->settings)
        delete p->settings;

    p->settings = 0;
    if(!p->source.isEmpty())
    {
        QDir().mkpath(QFileInfo(p->source).dir().path());
        p->settings = new QSettings(p->source, QSettings::IniFormat, this);
        initProperties();
    }

    emit sourceChanged();
}

QString AsemanSettings::source() const
{
    return p->source;
}

void AsemanSettings::propertyChanged()
{
    if(sender() != this)
        return;

    const int signalIndex = senderSignalIndex();
    if(signalIndex == -1)
        return;

    QMetaMethod signalObj = metaObject()->method(signalIndex);
    const QByteArray &propertyName = p->signalsProperties.value(signalObj.methodSignature());
    const QVariant &value = property(propertyName);
    if(p->settings)
        p->settings->setValue(PROPERTY_KEY(propertyName), value);
}

void AsemanSettings::initProperties()
{
    if(!p->settings || p->caregory.isEmpty())
        return;

    const QMetaObject *meta = metaObject();
    for(int i=0; i<meta->propertyCount(); i++)
    {
        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        const QByteArray &signalSign = property.notifySignal().methodSignature();
        if(propertyName == "source" || propertyName == "category" || propertyName == "objectName")
            continue;

        p->signalsProperties[signalSign] = propertyName;
        if(p->settings)
        {
            QVariant value = p->settings->value(PROPERTY_KEY(propertyName));
            if(!value.isNull())
                setProperty(propertyName, value);
        }

        connect(this, QByteArray::number(QSIGNAL_CODE)+signalSign,
                this, SLOT(propertyChanged()));
    }
}

AsemanSettings::~AsemanSettings()
{
    delete p;
}

