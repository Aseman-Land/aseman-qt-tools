#include "asemanquickviewwrapper.h"

AsemanQuickViewWrapper::AsemanQuickViewWrapper(AsemanQuickView *view, QObject *parent) :
    QObject(parent),
    mView(view)
{
    connect(mView, SIGNAL(fullscreenChanged()), SIGNAL(fullscreenChanged()));
    connect(mView, SIGNAL(statusBarHeightChanged()), SIGNAL(statusBarHeightChanged()));
    connect(mView, SIGNAL(navigationBarHeightChanged()), SIGNAL(navigationBarHeightChanged()));
    connect(mView, SIGNAL(rootChanged()), SIGNAL(rootChanged()));
    connect(mView, SIGNAL(focusedTextChanged()), SIGNAL(focusedTextChanged()));
    connect(mView, SIGNAL(layoutDirectionChanged()), SIGNAL(layoutDirectionChanged()));
    connect(mView, SIGNAL(backControllerChanged()), SIGNAL(backControllerChanged()));
    connect(mView, SIGNAL(reverseScrollChanged()), SIGNAL(reverseScrollChanged()));
    connect(mView, SIGNAL(fakeSignal()), SIGNAL(fakeSignal()));
    connect(mView, SIGNAL(closeRequest()), SIGNAL(closeRequest()));
    connect(mView, SIGNAL(destroyed(QObject*)), SLOT(viewDestroyed()));
}

AsemanQuickViewWrapper::~AsemanQuickViewWrapper()
{
}

void AsemanQuickViewWrapper::setFullscreen(bool stt)
{
    mView->setFullscreen(stt);
}

bool AsemanQuickViewWrapper::fullscreen() const
{
    return mView->fullscreen();
}

void AsemanQuickViewWrapper::setBackController(bool stt)
{
    mView->setBackController(stt);
}

bool AsemanQuickViewWrapper::backController() const
{
    return mView->backController();
}

void AsemanQuickViewWrapper::setReverseScroll(bool stt)
{
    mView->setReverseScroll(stt);
}

bool AsemanQuickViewWrapper::reverseScroll() const
{
    return mView->reverseScroll();
}

qreal AsemanQuickViewWrapper::statusBarHeight() const
{
    return mView->statusBarHeight();
}

qreal AsemanQuickViewWrapper::navigationBarHeight() const
{
    return mView->navigationBarHeight();
}

void AsemanQuickViewWrapper::setRoot(QObject *root)
{
    mView->setRoot(root);
}

QObject *AsemanQuickViewWrapper::root() const
{
    return mView->root();
}

void AsemanQuickViewWrapper::setFocusedText(QQuickItem *item)
{
    mView->setFocusedText(item);
}

QQuickItem *AsemanQuickViewWrapper::focusedText() const
{
    return mView->focusedText();
}

int AsemanQuickViewWrapper::layoutDirection() const
{
    return mView->layoutDirection();
}

void AsemanQuickViewWrapper::setLayoutDirection(int l)
{
    mView->setLayoutDirection(l);
}

qreal AsemanQuickViewWrapper::flickVelocity() const
{
    return mView->flickVelocity();
}

QWindow *AsemanQuickViewWrapper::window() const
{
#ifdef ASEMAN_QML_PLUGIN
    return 0;
#else
    return mView;
#endif
}

QSize AsemanQuickViewWrapper::screenSize() const
{
    return mView->screenSize();
}

void AsemanQuickViewWrapper::discardFocusedText()
{
    mView->discardFocusedText();
}

void AsemanQuickViewWrapper::tryClose()
{
    mView->tryClose();
}

void AsemanQuickViewWrapper::setMask(qreal x, qreal y, qreal width, qreal height)
{
    mView->setMask(x, y, width, height);
}

void AsemanQuickViewWrapper::move(qreal x, qreal y)
{
    mView->move(x, y);
}

void AsemanQuickViewWrapper::resize(qreal w, qreal h)
{
    mView->resize(w, h);
}

void AsemanQuickViewWrapper::viewDestroyed()
{
    deleteLater();
}
