#include <iostream>
#include <format>
#include <grpcpp/grpcpp.h>
#include <demo.pb.h>
#include <demo.grpc.pb.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpcdemo::DemoBook;
using grpcdemo::DemoBookRequest;
using grpcdemo::DemoBookReply;

class cppdemo_service : public DemoBook::Service {
	Status GetName(ServerContext* context, const DemoBookRequest* request, DemoBookReply* response) override {
		context->set_compression_algorithm(GRPC_COMPRESS_DEFLATE);
		response->set_name("aaa");
		std::cout << "id:" << request->id() << std::endl;
		return Status::OK;
	}

	Status GetByStream(::grpc::ServerContext* context, const DemoBookRequest* request, ::grpc::ServerWriter<DemoBookReply>* writer) override {
		std::cout << "s id:" << request->id() << std::endl;
		context->set_compression_algorithm(GRPC_COMPRESS_DEFLATE);
		DemoBookReply reply;
		reply.set_name("bbbb");
		writer->Write(reply);
		//writer->WriteLast(reply, {});// 不调用也是会退出
		for (int i = 0; i < 10; ++i) {
			Sleep(1000);
			writer->Write(reply);
		}
		return Status::OK;
	}

	Status GetByStream2(::grpc::ServerContext* context, ::grpc::ServerReaderWriter<DemoBookReply,DemoBookRequest>* stream)  override {
		DemoBookRequest request;
		while (stream->Read(&request)) {
			auto id = request.id();
			std::cout << "s2 id:" << id << std::endl;
			if (id == 0) {
				break;
			}
			DemoBookReply reply;
			reply.set_name(std::format("cccc {}", id));
			stream->Write(reply);
		}
		return Status::OK;
	}
};

int main() {
	std::string server_address("0.0.0.0:40041");
	cppdemo_service service;

	ServerBuilder builder;
	builder.SetDefaultCompressionAlgorithm(GRPC_COMPRESS_GZIP);
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	std::unique_ptr<Server> server(builder.BuildAndStart());

	std::cout << "listen: " << server_address << std::endl;

	server->Wait();
	return 0;
}