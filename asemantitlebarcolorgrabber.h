#ifndef ASEMANTITLEBARCOLORGRABBER_H
#define ASEMANTITLEBARCOLORGRABBER_H

#include <QObject>
#include <QWindow>

class AsemanTitleBarColorGrabberPrivate;
class AsemanTitleBarColorGrabber : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(bool autoRefresh READ autoRefresh WRITE setAutoRefresh NOTIFY autoRefreshChanged)
    Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY defaultColorChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    AsemanTitleBarColorGrabber(QObject *parent = 0);
    ~AsemanTitleBarColorGrabber();

    void setWindow(QWindow *win);
    QWindow *window() const;

    void setAutoRefresh(bool stt);
    bool autoRefresh() const;

    void setDefaultColor(const QColor &color);
    QColor defaultColor() const;

    QColor color() const;

public slots:
    void refresh();

signals:
    void windowChanged();
    void colorChanged();
    void autoRefreshChanged();
    void defaultColorChanged();

private slots:
    void activeChanged();

private:
    AsemanTitleBarColorGrabberPrivate *p;
};

#endif // ASEMANTITLEBARCOLORGRABBER_H
