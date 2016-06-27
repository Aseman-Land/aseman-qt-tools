#include "asemanencrypter.h"

QByteArray AsemanEncrypter::encrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Encryptor enc( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB, AsemanSimpleQtCryptor::NoChecksum );
    if(enc.encrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return data;
}

QByteArray AsemanEncrypter::decrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Decryptor dec( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB );
    if(dec.decrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return QByteArray();
}

void AsemanEncrypter::setKey(const QString &key)
{
    if(_keyStr == key)
        return;

    _keyStr = key;
    _key = QSharedPointer<AsemanSimpleQtCryptor::Key>(new AsemanSimpleQtCryptor::Key(_keyStr));
    Q_EMIT keyChanged();
}

QString AsemanEncrypter::key() const
{
    return _keyStr;
}

