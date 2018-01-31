#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include  "labelmodelcontroller.h"
#include "pinscontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<LabelModelController>("com.cps.qmlcomponents", 1, 0, "MyLabelController");
    qmlRegisterType<PinsController>("com.cps.qmlcomponents", 1, 0, "PinsController");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
