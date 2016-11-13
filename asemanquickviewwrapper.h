#ifndef ASEMANQUICKVIEWWRAPPER_H
#define ASEMANQUICKVIEWWRAPPER_H

#include <QObject>
#include "asemanquickview.h"

class AsemanQuickViewWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool reverseScroll READ reverseScroll WRITE setReverseScroll NOTIFY reverseScrollChanged)

    Q_PROPERTY(qreal statusBarHeight READ statusBarHeight NOTIFY statusBarHeightChanged)
    Q_PROPERTY(qreal navigationBarHeight READ navigationBarHeight NOTIFY navigationBarHeightChanged)

    Q_PROPERTY(QObject*    root        READ root        WRITE setRoot        NOTIFY rootChanged)
    Q_PROPERTY(QQuickItem* focusedText READ focusedText WRITE setFocusedText NOTIFY focusedTextChanged)

    Q_PROPERTY(int layoutDirection READ layoutDirection WRITE setLayoutDirection NOTIFY layoutDirectionChanged)
    Q_PROPERTY(bool reverseLayout READ reverseLayout NOTIFY layoutDirectionChanged)
    Q_PROPERTY(bool defaultLayout READ defaultLayout NOTIFY layoutDirectionChanged)
    Q_PROPERTY(QString offlineStoragePath READ offlineStoragePath WRITE setOfflineStoragePath NOTIFY offlineStoragePathChanged)

    Q_PROPERTY(qreal flickVelocity READ flickVelocity NOTIFY fakeSignal)
    Q_PROPERTY(QWindow* window READ window NOTIFY fakeSignal)

public:
    AsemanQuickViewWrapper(AsemanQuickView *view, QObject *parent = 0);
    ~AsemanQuickViewWrapper();

    void setReverseScroll(bool stt);
    bool reverseScroll() const;

    qreal statusBarHeight() const;
    qreal navigationBarHeight() const;

    void setRoot( QObject *root );
    QObject *root() const;

    void setFocusedText( QQuickItem *item );
    QQuickItem *focusedText() const;

    int layoutDirection() const;
    bool reverseLayout() const;
    bool defaultLayout() const;
    void setLayoutDirection( int l );

    void setBackController(bool stt);
    bool backController() const;

    qreal flickVelocity() const;

    QWindow *window() const;

    void setOfflineStoragePath(const QString &path);
    QString offlineStoragePath() const;

    Q_INVOKABLE void registerWindow(QQuickWindow *window);

public slots:
    void discardFocusedText();

signals:
    void fullscreenChanged();
    void statusBarHeightChanged();
    void navigationBarHeightChanged();
    void rootChanged();
    void focusedTextChanged();
    void layoutDirectionChanged();
    void backControllerChanged();
    void reverseScrollChanged();
    void fakeSignal();
    void closeRequest();
    void offlineStoragePathChanged();

private slots:
    void viewDestroyed();

private:
    AsemanQuickView *mView;
};

#endif // ASEMANQUICKVIEWWRAPPER_H
