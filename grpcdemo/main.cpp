#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "grpcbookdemoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GrpcBookDemoApi *api = new GrpcBookDemoApi();
    api->setHost("http://127.0.0.1:40041");
    engine.rootContext()->setContextProperty("grpcBook", api);

    const QUrl url(u"qrc:/grpcdemo/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
