#ifndef ASEMANQUICKOBJECT_H
#define ASEMANQUICKOBJECT_H

#include <QObject>
#include <QQmlListProperty>

#include "asemanglobals.h"

#define aqobject_cast(OBJECT) static_cast<AsemanQuickObject*>(OBJECT)

#define DEFINE_QML_PROEPRTY(PNAME) \
    private: \
        QVariant _##PNAME; \
    Q_SIGNALS: \
        void PNAME##Changed(); \
    public: \
        Q_PROPERTY(int PNAME READ PNAME WRITE set##PNAME NOTIFY PNAME##Changed) \
        int PNAME() const { return _##PNAME.toInt(); } \
        void set##PNAME(int PNAME) { SET_PROPERTY(PNAME) }

class AsemanQuickObjectPrivate;
class AsemanQuickObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

public:
    Q_INVOKABLE explicit AsemanQuickObject(QObject *parent = 0);
    ~AsemanQuickObject();

    QQmlListProperty<QObject> items();
    static bool isValid(AsemanQuickObject* obj);

signals:
    void itemsChanged();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

private:
    AsemanQuickObjectPrivate *p;
};

#endif // ASEMANQUICKOBJECT_H
