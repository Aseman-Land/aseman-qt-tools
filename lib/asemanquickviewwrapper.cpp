/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
