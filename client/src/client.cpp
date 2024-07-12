#include "enums.hpp"
#include "client_method.hpp"
#include "utils.hpp"


namespace energy
{
    void RunClient()
    {
        EnergyMeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

        MeterInfor meter;
        meter.set_line(Lines::ARES);
        meter.set_model("Model X");

        // Cliente faz uma requisição para criar um Medidor de energia.
        std::cout << "***** INICIO CREATEMETER *****" << std::endl;
        MeterCompleteInfor response = client.CreateMeter(meter);
        std::cout << "Medidor de energia criado.\n";
        std::cout << "Response: " << response.model() << " Line: " << response.line() << std::endl;
        std::cout << "***** FINAL CREATEMETER *****" << std::endl;

        // Cliente faz uma requisição para saber informações de um Medidor pelo ID.
        MeterID meter_id;
        meter_id.set_id(1);
        std::cout << "***** INICIO READMETER *****" << std::endl;
        response = client.ReadMeter(meter_id);
        std::cout << "Dados retornados: response: " << response.model() << std::endl;
        std::cout << "***** FINAL READMETER *****" << std::endl;

        // Cliente deleta uma Medidor de energia da lista pelo ID.
        std::cout << "***** INICIO DELETEMETER *****" << std::endl;
        client.DeleteMeter(meter_id);
        std::cout << "***** FINAL DELETEMETER *****" << std::endl;
    }

}