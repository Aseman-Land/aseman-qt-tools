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

public:
    AsemanQmlSmartComponent(QObject *parent = 0);
    ~AsemanQmlSmartComponent();

    void setSource(const QUrl &url);
    QUrl source() const;

    int status() const;
    QString error() const;

public slots:
    QObject *createObject(QObject *parent, const QVariantMap &data = QVariantMap());

signals:
    void sourceChanged();
    void statusChanged();
    void errorChanged();

private slots:
    void statusChanged(QQmlComponent::Status status);

private:
    AsemanQmlSmartComponentPrivate *p;
};

#endif // ASEMANQMLSMARTCOMPONENT_H
