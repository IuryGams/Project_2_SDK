#include <locale.h>
#include <iostream>
#include <thread>

#include "menu.hpp"
#include "server.hpp"
#include "client.hpp"

int main () 
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    std::thread server_thread(energy::RunServer);
    // std::thread client_thread(energy::RunClient);

    // Aguardar até que ambas as threads terminem
    // client_thread.join();
    server_thread.join();

    std::cout << "Programa encerrado!\n";
    std::exit(0);
    return 0;
}
