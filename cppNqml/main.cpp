#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include <QTimer>

#include "segmentdemo.h"
#include "globaldemo.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "cppNqml_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }


    QQmlApplicationEngine engine;

    // 注册类
    qmlRegisterType<SegmentDemo>("SegmentDemo", 1, 0, "SegmentObject");

    // 注册对象
    GlobalDemo *globalDemo = new GlobalDemo();
    engine.rootContext()->setContextProperty("globalDemo", globalDemo);

    // 计时器
    QTimer *timer = new QTimer(&engine);
    QObject::connect(timer, &QTimer::timeout, &app, [globalDemo] {
        globalDemo->set_timestamp(globalDemo->get_timestamp() + 1);
    });
    timer->start(1000);

    const QUrl url(u"qrc:/cppNqml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
