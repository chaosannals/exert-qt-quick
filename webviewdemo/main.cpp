#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebView>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtWebView::initialize();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/webviewdemo/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
