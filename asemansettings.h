#ifndef ASEMANSETTINGS_H
#define ASEMANSETTINGS_H

#include <QObject>

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

signals:
    void categoryChanged();
    void sourceChanged();

private slots:
    void propertyChanged();
    void initProperties();

private:
    AsemanSettingsPrivate *p;
};

#endif // ASEMANSETTINGS_H
