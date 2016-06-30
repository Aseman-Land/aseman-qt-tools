#ifndef ASEMANKEYCHAIN_H
#define ASEMANKEYCHAIN_H

#include <QObject>
#include <QJSValue>

class AsemanKeychainPrivate;
class AsemanKeychain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString service READ service WRITE setService NOTIFY serviceChanged)
public:
    AsemanKeychain(QObject *parent = 0);
    ~AsemanKeychain();

    void setService(const QString &service);
    QString service() const;

public slots:
    QString read(const QString &key, const QJSValue &jsCallback = QJSValue());
    QByteArray readData(const QString &key, const QJSValue &jsCallback = QJSValue());

    bool write(const QString &key, const QString &data, const QJSValue &jsCallback = QJSValue());
    bool writeData(const QString &key, const QByteArray &data, const QJSValue &jsCallback = QJSValue());

    bool remove(const QString &key, const QJSValue &jsCallback = QJSValue());

signals:
    void serviceChanged();

private:
    AsemanKeychainPrivate *p;
};

#endif // ASEMANKEYCHAIN_H
