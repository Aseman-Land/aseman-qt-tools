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

#include "../../asemanapplication.h"
#include "../../asemanqmlengine.h"

#include <QGuiApplication>
#include <QPalette>

int main(int argc, char *argv[])
{
//    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    AsemanApplication app(argc, argv);

    QPalette palette = app.palette();
    palette.setColor(QPalette::Highlight, QColor("#0d80ec"));

    AsemanQmlEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
