#include "enums.hpp"
#include "client_method.hpp"
#include "utils.hpp"

namespace energy
{
    void RunClient()
    {
        EnergyMeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

        // Cria um novo medidor de energia
        if (client.CreateMeter(18, static_cast<int>(Lines::ARES), "Model X"))
        {
            std::cout << "Medidor criado com sucesso." << std::endl;
        }
        else
        {
            std::cout << "Falha ao criar o medidor." << std::endl;
        }

        // Lê os detalhes do medidor criado
        if (client.ReadMeter(1))
        {
            std::cout << "Leitura do medidor realizada com sucesso." << std::endl;
        }
        else
        {
            std::cout << "Falha ao ler o medidor." << std::endl;
        }

        // Obtém todos os medidores
        client.GetAllMeters();

        // Deleta o medidor criado
        if (client.DeleteMeter(1))
        {
            std::cout << "Medidor deletado com sucesso." << std::endl;
        }
        else
        {
            std::cout << "Falha ao deletar o medidor." << std::endl;
        }

        // Obtém todas as linhas disponíveis
        client.GetAllLines();

        // Obtém todos os modelos por linha
        client.GetModelsByLine("ARES");
    }

}