#include "asemantexttools.h"

#include <QTextDocument>

class AsemanTextToolsPrivate
{
public:
    QTextDocument *doc;
};

AsemanTextTools::AsemanTextTools(QObject *parent) :
    QObject(parent)
{
    p = new AsemanTextToolsPrivate;
    p->doc = new QTextDocument(this);
}

qreal AsemanTextTools::htmlWidth(const QString &html)
{
    p->doc->setHtml(html);
    return p->doc->size().width() + 10;
}

AsemanTextTools::~AsemanTextTools()
{
    delete p;
}

