#include "grpcbookdemoapi.h"

#include <QGrpcHttp2Channel>

GrpcBookDemoApi::GrpcBookDemoApi(QObject *parent)
    : QObject{parent},
    client(new grpcdemo::DemoBook::Client)
{

}

GrpcBookDemoApi::State GrpcBookDemoApi::login() {
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
    // auto stream = client->streamMessageList(qtgrpc::examples::chat::None());
    // QObject::connect(stream.get(), &QGrpcStream::errorOccurred, this,
    //                  [this, stream](const QGrpcStatus &status) {
    //                      qCritical()
    //                          << "Stream error(" << status.code() << "):" << status.message();
    //                      if (status.code() == QGrpcStatus::Unauthenticated) {
    //                          emit authFailed();
    //                      } else {
    //                          emit networkError(status.message());
    //                          setState(Disconnected);
    //                      }
    //                  });

    // QObject::connect(stream.get(), &QGrpcStream::finished, this,
    //                  [this, stream]() { setState(Disconnected); });

    // QObject::connect(
    //     stream.get(), &QGrpcStream::messageReceived, this, [this, name, password, stream]() {
    //         if (m_userName != name) {
    //             m_userName = name;
    //             m_password = password;
    //             emit userNameChanged();
    //         }
    //         setState(Connected);
    //         m_messages.append(stream->read<qtgrpc::examples::chat::ChatMessages>().messages());
    //     });
}

QString GrpcBookDemoApi::find(int id) {
    grpcdemo::DemoBookRequest request;
    request.setId_proto(id);
    auto reply = client->GetName(request)->read<grpcdemo::DemoBookReply>();
    return reply.name();
}
