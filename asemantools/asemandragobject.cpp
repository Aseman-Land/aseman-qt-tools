#include "asemandragobject.h"
#include "asemanmimedata.h"

#include <QDrag>
#include <QPointer>
#include <QMimeData>
#include <QDebug>
#include <QPixmap>

class AsemanDragObjectPrivate
{
public:
    QPointer<AsemanMimeData> mime;
    QPointer<QQuickItem> source;
    QUrl image;
    int dropAction;
    QPoint hotSpot;

    bool onDrag;
};

AsemanDragObject::AsemanDragObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanDragObjectPrivate;
    p->dropAction = Qt::MoveAction;
    p->onDrag = false;
}

void AsemanDragObject::setMimeData(AsemanMimeData *mime)
{
    if(p->mime == mime)
        return;

    p->mime = mime;
    emit mimeDataChanged();
}

AsemanMimeData *AsemanDragObject::mimeData() const
{
    return p->mime;
}

void AsemanDragObject::setDropAction(int act)
{
    if(p->dropAction == act)
        return;

    p->dropAction = act;
    emit dropActionChanged();
}

int AsemanDragObject::dropAction() const
{
    return p->dropAction;
}

void AsemanDragObject::setSource(QQuickItem *item)
{
    if(p->source == item)
        return;

    p->source = item;
    emit sourceChanged();
}

QQuickItem *AsemanDragObject::source() const
{
    return p->source;
}

void AsemanDragObject::setImage(const QUrl &url)
{
    if(p->image == url)
        return;

    p->image = url;
    emit imageChanged();
}

QUrl AsemanDragObject::image() const
{
    return p->image;
}

bool AsemanDragObject::dragging() const
{
    return p->onDrag;
}

void AsemanDragObject::setHotSpot(const QPoint &point)
{
    if(p->hotSpot == point)
        return;

    p->hotSpot = point;
    emit hotSpotChanged();
}

QPoint AsemanDragObject::hotSpot() const
{
    return p->hotSpot;
}

int AsemanDragObject::start()
{
    if(!p->source)
    {
        qDebug() << "DragObject: source property is null!";
        return -1;
    }
    if(p->onDrag)
        return -1;

    p->onDrag = true;
    emit draggingChanged();

    QMimeData *mime = new QMimeData();
    if(p->mime)
    {
        mime->setText(p->mime->text());
        mime->setHtml(p->mime->html());
        mime->setUrls(p->mime->urls());

        const QVariantMap &map = p->mime->dataMap();
        QMapIterator<QString,QVariant> i(map);
        while(i.hasNext())
        {
            i.next();
            mime->setData(i.key(), i.value().toByteArray());
        }
    }

    QDrag *drag = new QDrag(p->source);
    drag->setMimeData(mime);
    if(p->image.isValid())
    {
        QString path = p->image.toString();
        if(path.left(4) == "qrc:")
            path = path.mid(3);

        drag->setPixmap( QPixmap(path) );
    }
    if(!p->hotSpot.isNull())
        drag->setHotSpot(p->hotSpot);

    int res = drag->exec( static_cast<Qt::DropAction>(p->dropAction) );

#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
    drag->deleteLater();
#endif

    p->source->ungrabMouse();
    p->source->ungrabTouchPoints();

    p->onDrag = false;
    emit draggingChanged();

    return res;
}

AsemanDragObject::~AsemanDragObject()
{
    delete p;
}

