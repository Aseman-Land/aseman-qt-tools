#ifndef ASEMANWINDOWDETAILS_H
#define ASEMANWINDOWDETAILS_H

#include <QObject>
#include <QWindow>
#include <QScreen>

class AsemanWindowDetailsPrivate;
class AsemanWindowDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(QScreen* screen READ screen NOTIFY screenChanged)

public:
    AsemanWindowDetails(QObject *parent = 0);
    ~AsemanWindowDetails();

    QWindow *window() const;
    void setWindow(QWindow *window);

    QScreen *screen() const;

signals:
    void windowChanged();
    void screenChanged();

private:
    AsemanWindowDetailsPrivate *p;
};

#endif // ASEMANWINDOWDETAILS_H
