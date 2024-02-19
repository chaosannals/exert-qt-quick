#ifndef GRPCBOOKDEMOAPI_H
#define GRPCBOOKDEMOAPI_H

#include <QObject>
#include <QQmlEngine>
#include "demo.qpb.h"
#include "demo_client.grpc.qpb.h"

class GrpcBookDemoApi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)
public:
    enum State {
        Disconnected = 0,
        Connecting = 1,
        Connected = 2,
    };
    Q_ENUM(State)

    explicit GrpcBookDemoApi(QObject *parent = nullptr);
    ~ GrpcBookDemoApi() override { delete client; }

    QString getHost() const { return host; }
    void setHost(const QString &v) { host = v; emit hostChanged(); }

    Q_INVOKABLE State login();
    Q_INVOKABLE QString find(int id);
signals:
    void hostChanged();
private:
    QString host;
    State state;
    grpcdemo::DemoBook::Client *client;
};

#endif // GRPCBOOKDEMOAPI_H
