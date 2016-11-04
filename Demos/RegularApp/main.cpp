#include "../../asemanapplication.h"
#include "../../asemanqmlengine.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
//    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    AsemanApplication app(argc, argv);

    AsemanQmlEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
