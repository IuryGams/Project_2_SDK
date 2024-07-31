#include <iostream>
#include "server.hpp"

namespace energy
{
    static const std::string server_address_ = "0.0.0.0:50051";

    void Server::RunServer()
    {
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);

        server_ = builder.BuildAndStart();
        std::cout << "Server is running on the port " << server_address_ << std::endl;
        server_->Wait();
    }

    void Server::StopServer()
    {
        if (server_)
        {
            server_->Shutdown();
            server_->Wait();
            server_.reset();
            std::cout << "Server is down!\n";
        }

    }

}
