#ifndef ASEMANMOUSEEVENTLISTENER_H
#define ASEMANMOUSEEVENTLISTENER_H

#include <QQuickItem>

class AsemanMouseEventListenerPrivate;
class AsemanMouseEventListener : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(qreal mouseY READ mouseY NOTIFY mouseYChanged)
    Q_PROPERTY(QPointF mousePosition READ mousePosition NOTIFY mousePositionChanged)

public:
    AsemanMouseEventListener(QQuickItem *parent = Q_NULLPTR);
    ~AsemanMouseEventListener();

    qreal mouseX() const;
    qreal mouseY() const;
    QPointF mousePosition() const;

public Q_SLOTS:
    void ignoreEvent();
    void acceptEvent();

Q_SIGNALS:
    void mouseXChanged();
    void mouseYChanged();
    void mousePositionChanged();
    void mousePressed();
    void mouseReleased();

protected:
    bool childMouseEventFilter(QQuickItem *item, QEvent *event);

private:
    AsemanMouseEventListenerPrivate *p;
};

#endif // ASEMANMOUSEEVENTLISTENER_H
