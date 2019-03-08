#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <thresholdimg.h>
#include <alpainter.h>
#include <calculator.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ThresholdImg>("an.qt.ThresholdImg",1,0,"ThresholdImg");
    qmlRegisterType<ALPainter>("an.qt.ALPainter", 1, 0, "ALPainter");
    qmlRegisterType<Calculator>("an.qt.Calculator",1,0,"Calculator");
    //qmlRegisterType<CSVWriter>("an.qt.CSVWriter",1,0,"CSVWriter");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
