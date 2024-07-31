#include "operations.hpp"
#include "server.hpp"
#include "client.hpp"

#include <locale.h>
#include <iostream>
#include <thread>

    void RunServer()
    {
        grpc::ServerBuilder builder;
        energy::EnergyMeterServiceImpl service_;

        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);

        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        std::cout << "Server is running on the port " << "0.0.0.0:50051" << std::endl;
        server->Wait();
    }

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // energy::Server server;

    std::thread server_thread(RunServer);

    // Inicia o servidor em um thread separado
    // server.RunServer();

    // Para o servidor e aguarda o término do thread
    // server.StopServer();

    // std::thread client_thread(energy::RunClient);

    // client_thread.join();
    server_thread.join();

    std::cout << "Programa encerrado!\n";
    return 0;
}
