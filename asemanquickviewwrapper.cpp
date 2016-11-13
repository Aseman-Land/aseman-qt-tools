#include "asemanquickviewwrapper.h"

AsemanQuickViewWrapper::AsemanQuickViewWrapper(AsemanQuickView *view, QObject *parent) :
    QObject(parent),
    mView(view)
{
    connect(mView, SIGNAL(statusBarHeightChanged()), SIGNAL(statusBarHeightChanged()));
    connect(mView, SIGNAL(navigationBarHeightChanged()), SIGNAL(navigationBarHeightChanged()));
    connect(mView, SIGNAL(rootChanged()), SIGNAL(rootChanged()));
    connect(mView, SIGNAL(focusedTextChanged()), SIGNAL(focusedTextChanged()));
    connect(mView, SIGNAL(layoutDirectionChanged()), SIGNAL(layoutDirectionChanged()));
    connect(mView, SIGNAL(reverseScrollChanged()), SIGNAL(reverseScrollChanged()));
    connect(mView, SIGNAL(fakeSignal()), SIGNAL(fakeSignal()));
    connect(mView, SIGNAL(closeRequest()), SIGNAL(closeRequest()));
    connect(mView, SIGNAL(destroyed(QObject*)), SLOT(viewDestroyed()));
    connect(mView, SIGNAL(offlineStoragePathChanged()), SIGNAL(offlineStoragePathChanged()));
}

AsemanQuickViewWrapper::~AsemanQuickViewWrapper()
{
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

bool AsemanQuickViewWrapper::reverseLayout() const
{
    return mView->layoutDirection() == Qt::RightToLeft;
}

bool AsemanQuickViewWrapper::defaultLayout() const
{
    return mView->layoutDirection() != Qt::RightToLeft;
}

qreal AsemanQuickViewWrapper::flickVelocity() const
{
    return mView->flickVelocity();
}

QWindow *AsemanQuickViewWrapper::window() const
{
    return 0;
}

void AsemanQuickViewWrapper::setOfflineStoragePath(const QString &path)
{
    mView->setOfflineStoragePath(path);
}

QString AsemanQuickViewWrapper::offlineStoragePath() const
{
    return mView->offlineStoragePath();
}

void AsemanQuickViewWrapper::registerWindow(QQuickWindow *window)
{
    mView->registerWindow(window);
}

void AsemanQuickViewWrapper::discardFocusedText()
{
    mView->discardFocusedText();
}

void AsemanQuickViewWrapper::viewDestroyed()
{
    deleteLater();
}
