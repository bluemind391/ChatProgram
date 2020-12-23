#define WIN32_LEAN_AND_MEAN

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <memory>

#include "ChatClient.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qmlRegisterType<ChatClient>("ChatClient", 1, 0, "ChatClient");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* root = engine.rootObjects()[0];

    ChatClient::getInstance().SetObject(root);
    ChatClient::getInstance().SetWindow(qobject_cast<QQuickWindow*>(root));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
