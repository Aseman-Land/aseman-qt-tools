/*
    Copyright (C) 2014 Aseman
    http://aseman.co

    This Project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This Project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANNOTIFICATION_H
#define ASEMANNOTIFICATION_H

#include <QObject>
#include <QStringList>

#ifdef LINUX_NATIVE_ASEMAN_NOTIFICATION
class QDBusMessage;
class AsemanNotificationPrivate;
class AsemanNotification : public QObject
{
    Q_OBJECT
public:
    AsemanNotification(QObject *parent = 0);
    ~AsemanNotification();

public slots:
    uint sendNotify(const QString & title, const QString & body, const QString & icon, uint replace_id = 0, int timeOut = 3000 , const QStringList &actions = QStringList());
    void closeNotification( uint id );

signals:
    void notifyClosed( uint id );
    void notifyTimedOut( uint id );
    void notifyAction( uint id, const QString & action );

private slots:
    void notificationClosed( const QDBusMessage & dmsg );
    void actionInvoked( const QDBusMessage & dmsg );

private:
    AsemanNotificationPrivate *p;
};
#else
class AsemanNotification : public QObject
{
    Q_OBJECT
public:
    AsemanNotification(QObject *parent = 0){}
    ~AsemanNotification(){}

public slots:
    uint sendNotify(const QString & title, const QString & body, const QString & icon, uint replace_id = 0, int timeOut = 3000 , const QStringList &actions = QStringList()){}
    void closeNotification( uint id ){}

signals:
    void notifyClosed( uint id );
    void notifyTimedOut( uint id );
    void notifyAction( uint id, const QString & action );
};
#endif

#endif // ASEMANNOTIFICATION_H
