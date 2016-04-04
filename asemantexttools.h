#ifndef ASEMANTEXTTOOLS_H
#define ASEMANTEXTTOOLS_H

#include <QObject>

class AsemanTextToolsPrivate;
class AsemanTextTools : public QObject
{
    Q_OBJECT
public:
    AsemanTextTools(QObject *parent = 0);
    ~AsemanTextTools();

    qreal htmlWidth(const QString &html);

private:
    AsemanTextToolsPrivate *p;
};

#endif // ASEMANTEXTTOOLS_H
