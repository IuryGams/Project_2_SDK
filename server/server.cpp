#include <iostream>
#include "energy_meter_services.hpp"
#include "server.hpp"

namespace energy
{
    void RunServer()
    {
        std::string server_address("0.0.0.0:50051");
        energy::EnergyMeterServiceImpl service;

        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);

        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        std::cout << "Server rodando em " << server_address << std::endl;
        server->Wait();
    }
}
