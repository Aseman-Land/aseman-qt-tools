#ifndef ASEMANQMLSMARTCOMPONENT_H
#define ASEMANQMLSMARTCOMPONENT_H

#include <QObject>
#include <QQmlComponent>
#include <QJSValue>
#include <QUrl>

class AsemanQmlSmartComponentPrivate;
class AsemanQmlSmartComponent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QQmlComponent* component READ component NOTIFY componentChanged)

public:
    AsemanQmlSmartComponent(QObject *parent = 0);
    ~AsemanQmlSmartComponent();

    void setSource(const QUrl &url);
    QUrl source() const;

    int status() const;
    QString error() const;

    QQmlComponent *component() const;

signals:
    void sourceChanged();
    void statusChanged();
    void errorChanged();
    void componentChanged();
    void ready();

private slots:
    void statusChanged(QQmlComponent::Status status);

private:
    AsemanQmlSmartComponentPrivate *p;
};

#endif // ASEMANQMLSMARTCOMPONENT_H
