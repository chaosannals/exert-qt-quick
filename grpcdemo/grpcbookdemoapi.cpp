#include "grpcbookdemoapi.h"

#include <QGrpcHttp2Channel>

GrpcBookDemoApi::GrpcBookDemoApi(QObject *parent)
    : QObject{parent},
    client(new grpcdemo::DemoBook::Client)
{

}

void GrpcBookDemoApi::login() {
    QUrl url(host);

    // ![0]
    QGrpcChannelOptions channelOptions(url);
    // 带一些原信息，目前示例不需要。
    // QGrpcMetadata metadata = {
    //   { "user-name", { name.toUtf8() } },
    //   { "user-password", { password.toUtf8() } },
    // };
    // channelOptions.withMetadata(metadata);
    std::shared_ptr<QAbstractGrpcChannel> channel = std::make_shared<QGrpcHttp2Channel>(
        channelOptions);
    client->attachChannel(channel);

    // 流参数
    grpcdemo::DemoBookRequest request;
    request.setId_proto(123456);
    auto stream = client->streamGetByStream(request);
    QObject::connect(stream.get(), &QGrpcStream::errorOccurred, this,
                     [this, stream](const QGrpcStatus &status) {
        qDebug("grpc stream error");
        qCritical()
             << "Stream error(" << status.code() << "):" << status.message();
        if (status.code() == QGrpcStatus::Unauthenticated) {
             emit authFailed();
        } else {
            emit networkError(status.message());
            setState(Disconnected);
        }
    });

    QObject::connect(stream.get(), &QGrpcStream::finished, this,
                     [this, stream]() {
        qDebug("grpc stream finished");
        setState(Disconnected);
    });

    QObject::connect(
        stream.get(), &QGrpcStream::messageReceived, this, [this, stream]() {
            auto r = stream->read<grpcdemo::DemoBookReply>();
            qDebug("grpc stream messageReceived %s", r.name().toStdString().c_str());
            setState(Connected);
        });
}

QString GrpcBookDemoApi::find(int id) {
    grpcdemo::DemoBookRequest request;
    request.setId_proto(id);
    auto reply = client->GetName(request);
    auto r = reply->read<grpcdemo::DemoBookReply>();
    return r.name();
}
