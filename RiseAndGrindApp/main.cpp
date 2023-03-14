#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "equipmentdatabase.h"
#include "engine.h"
#include "searchparameters.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    EquipmentDatabase * d = new EquipmentDatabase();
    Engine setEngine(d);
    d->LoadData();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    SearchParameters p;
    p.AddSkill(71, 2);
    p.AddSkill(24, 1);
    p.AddSkill(37, 1);
    setEngine.FindSets(p, 10);
    return app.exec();
}
