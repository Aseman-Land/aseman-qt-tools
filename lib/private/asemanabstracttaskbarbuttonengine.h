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

#ifndef ASEMANABSTRACTTASKBARBUTTONENGINE_H
#define ASEMANABSTRACTTASKBARBUTTONENGINE_H

#include <QtGlobal>
#include <QVariant>

class QWindow;
class AsemanAbstractTaskbarButtonEngine
{
public:
    virtual ~AsemanAbstractTaskbarButtonEngine(){}
    virtual void updateBadgeNumber(int num) = 0;
    virtual void updateProgress(qreal progress) = 0;
    virtual void updateLauncher(const QString &launcher) {Q_UNUSED(launcher)}
    virtual void updateWindow(QWindow *window) {Q_UNUSED(window)}
    virtual void userAttention() {}
};

#endif // ASEMANABSTRACTTASKBARBUTTONENGINE_H
