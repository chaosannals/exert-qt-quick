#include <iostream>
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
	Status GetName(ServerContext* context, const DemoBookRequest* request, DemoBookReply* response) {
		context->set_compression_algorithm(GRPC_COMPRESS_DEFLATE);
		response->set_name("aaa");
		std::cout << "id:" << request->id() << std::endl;
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