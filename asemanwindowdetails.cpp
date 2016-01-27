#include "asemanwindowdetails.h"

#include <QPointer>
#include <QGuiApplication>

class AsemanWindowDetailsPrivate
{
public:
    QPointer<QWindow> window;
};

AsemanWindowDetails::AsemanWindowDetails(QObject *parent) :
    QObject(parent)
{
    p = new AsemanWindowDetailsPrivate;
}

QWindow *AsemanWindowDetails::window() const
{
    return p->window;
}

void AsemanWindowDetails::setWindow(QWindow *window)
{
    if(p->window == window)
        return;

    if(p->window)
    {
        disconnect(p->window, SIGNAL(screenChanged(QScreen*)),
                   this, SIGNAL(screenChanged()));
    }

    p->window = window;
    if(p->window)
    {
        connect(p->window, SIGNAL(screenChanged(QScreen*)),
                this, SIGNAL(screenChanged()));
    }

    emit windowChanged();
    emit screenChanged();
}

QScreen *AsemanWindowDetails::screen() const
{
    if(p->window)
        return p->window->screen();
    else
        return QGuiApplication::primaryScreen();
}

AsemanWindowDetails::~AsemanWindowDetails()
{
    delete p;
}

