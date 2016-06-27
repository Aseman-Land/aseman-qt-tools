#ifndef ASEMANENCRYPTER_H
#define ASEMANENCRYPTER_H

#include "asemansimpleqtcryptor.h"

class AsemanEncrypter: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)

public:
    AsemanEncrypter(QObject *parent = 0): QObject(parent){}
    ~AsemanEncrypter(){}

    void setKey(const QString &key);
    QString key() const;

public Q_SLOTS:
    QByteArray encrypt(const QByteArray &data);
    QByteArray decrypt(const QByteArray &data);

Q_SIGNALS:
    void keyChanged();

private:
    QString _keyStr;
    QSharedPointer<AsemanSimpleQtCryptor::Key> _key;
};

#endif // ASEMANENCRYPTER_H
