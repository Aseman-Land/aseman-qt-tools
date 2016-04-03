#ifndef ASEMANSETTINGS_H
#define ASEMANSETTINGS_H

#include <QObject>
#include <QVariant>

class AsemanSettingsPrivate;
class AsemanSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
    AsemanSettings(QObject *parent = 0);
    ~AsemanSettings();

    void setCategory(const QString &category);
    QString category() const;

    void setSource(const QString &source);
    QString source() const;

public Q_SLOTS:
    void setValue(const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant());
    void remove(const QString &key);
    QStringList keys() const;

signals:
    void categoryChanged();
    void sourceChanged();
    void valueChanged();

private slots:
    void propertyChanged();
    void initProperties();

private:
    AsemanSettingsPrivate *p;
};

#endif // ASEMANSETTINGS_H
