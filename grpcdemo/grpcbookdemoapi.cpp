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

    // 流返回结果
    // 接收长连接 + 发送短连接  可以完成即时效果。
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

    // QT 封装的 grpc 不支持参数流，生成代码里面会自动忽略掉带 stream 参数的方法。
    // 流参数 + 流结果 = 长连接
}

QString GrpcBookDemoApi::find(int id) {
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

    grpcdemo::DemoBookRequest request;
    request.setId_proto(id); // id 这个名字比较特殊，导致多了 _proto 后缀。
    auto reply = client->GetName(request); // 即使服务器不开，连不上也不会报错，内部被 QT 封装处理了。
    auto r = reply->read<grpcdemo::DemoBookReply>(); // 八成 QT 的这个封装就没打算做返回值，示例代码是通过 另一个 stream 返回值获取数据。
    return r.name();
}
