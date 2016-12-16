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

#ifndef ASEMANFONTHANDLER_H
#define ASEMANFONTHANDLER_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <QFont>
#include <QMap>

class AsemanFontHandlerPrivate;
class AsemanFontHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap fonts READ fonts WRITE setFonts NOTIFY fontsChanged)

public:
    AsemanFontHandler(QObject *parent = 0);
    ~AsemanFontHandler();

    QVariantMap fonts();
    void setFonts(const QVariantMap &fonts);

    Q_INVOKABLE QFont fontOf(int script);
    Q_INVOKABLE QString textToHtml(const QString &text);

    Q_INVOKABLE QByteArray save();
    Q_INVOKABLE void load(const QByteArray &data);

public slots:
#ifdef QT_WIDGETS_LIB
    void openFontChooser();
#endif

signals:
    void fontsChanged();

private slots:
    void init();
#ifdef QT_WIDGETS_LIB
    void currentIndexChanged(const QString &key);
    void currentFontChanged(const QFont &font);
#endif

private:
    AsemanFontHandlerPrivate *p;
};

#endif // ASEMANFONTHANDLER_H
