#include "asemanmouseeventlistener.h"

#include <QDebug>

class AsemanMouseEventListenerPrivate
{
public:
    QPointF point;
    bool ignoreEvent;
};

AsemanMouseEventListener::AsemanMouseEventListener(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new AsemanMouseEventListenerPrivate;
    p->ignoreEvent = false;
    setFiltersChildMouseEvents(true);
}

bool AsemanMouseEventListener::childMouseEventFilter(QQuickItem *item, QEvent *e)
{
    QMouseEvent *mevent = static_cast<QMouseEvent*>(e);
    switch(static_cast<int>(e->type()))
    {
    case QEvent::MouseMove:
    {
        QPointF newP = mapFromItem(item, mevent->pos());
        bool xChanged = (newP.x() != p->point.x());
        bool yChanged = (newP.y() != p->point.y());
        p->point = newP;
        if(xChanged) Q_EMIT mouseXChanged();
        if(yChanged) Q_EMIT mouseYChanged();
        Q_EMIT mousePositionChanged();
        break;
    }
    case QEvent::MouseButtonPress:
        p->point = mapFromItem(item, mevent->pos());
        Q_EMIT mousePressed();
        break;
    case QEvent::MouseButtonRelease:
        p->point = mapFromItem(item, mevent->pos());
        Q_EMIT mouseReleased();
        break;

    default:
        p->ignoreEvent = false;
        break;
    }

    if(p->ignoreEvent)
    {
        p->ignoreEvent = false;
        return true;
    }
    else
        return QQuickItem::childMouseEventFilter(item, e);
}

qreal AsemanMouseEventListener::mouseX() const
{
    return p->point.x();
}

qreal AsemanMouseEventListener::mouseY() const
{
    return p->point.y();
}

QPointF AsemanMouseEventListener::mousePosition() const
{
    return p->point;
}

void AsemanMouseEventListener::ignoreEvent()
{
    p->ignoreEvent = true;
}

void AsemanMouseEventListener::acceptEvent()
{
    p->ignoreEvent = false;
}

AsemanMouseEventListener::~AsemanMouseEventListener()
{
    delete p;
}
