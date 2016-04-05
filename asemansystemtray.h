#ifndef ASEMANSYSTEMTRAY_H
#define ASEMANSYSTEMTRAY_H

#include "aseman_macros.h"
#include "asemanquickobject.h"

#include <QUrl>
#include <QSystemTrayIcon>

class AsemanSystemTrayPrivate;
class AsemanSystemTray : public AsemanQuickObject
{
    Q_OBJECT
    Q_ENUMS(ActivateReason)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(int badgeCount READ badgeCount WRITE setBadgeCount NOTIFY badgeCountChanged)
    Q_PROPERTY(QColor badgeFillColor READ badgeFillColor WRITE setBadgeFillColor NOTIFY badgeFillColorChanged)
    Q_PROPERTY(QColor badgeStrokeColor READ badgeStrokeColor WRITE setBadgeStrokeColor NOTIFY badgeStrokeColorChanged)
    Q_PROPERTY(QColor badgeTextColor READ badgeTextColor WRITE setBadgeTextColor NOTIFY badgeTextColorChanged)
    Q_PROPERTY(QStringList menu READ menu WRITE setMenu NOTIFY menuChanged)

public:
    enum ActivateReason {
        ActivateUnknown,
        ActivateContext,
        ActivateDoubleClick,
        ActivateTrigger,
        ActivateMiddleClick
    };

    AsemanSystemTray(QObject *parent = 0);
    ~AsemanSystemTray();

    void setVisible(bool visible);
    bool visible() const;

    void setIcon(const QUrl &icon);
    QUrl icon() const;

    void setBadgeCount(int badgeCount);
    int badgeCount() const;

    void setBadgeFillColor(const QColor &color);
    QColor badgeFillColor() const;

    void setBadgeStrokeColor(const QColor &color);
    QColor badgeStrokeColor() const;

    void setBadgeTextColor(const QColor &color);
    QColor badgeTextColor() const;

    void setMenu(const QStringList &menu);
    QStringList menu() const;

signals:
    void visibleChanged();
    void activated(int reason);
    void iconChanged();
    void badgeCountChanged();
    void badgeFillColorChanged();
    void badgeStrokeColorChanged();
    void badgeTextColorChanged();
    void menuChanged();
    void menuTriggered(int index);

public slots:

protected:
    void activated_slt(QSystemTrayIcon::ActivationReason reason);
    void refreshIcon();
    QImage generateIcon(const QString & img, int count );
    void refreshVisible();

private:
    AsemanSystemTrayPrivate *p;
};

#endif // ASEMANSYSTEMTRAY_H
