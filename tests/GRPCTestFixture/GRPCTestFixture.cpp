#include "server.hpp"
#include "energy_meter_services.hpp"
#include "GRPCTestFixture.hpp"

namespace test
{
    void run_server()
    {
        std::system("start /B PROJECT_INTEGRATION.exe");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    GRPCTestFixture::GRPCTestFixture()
    {
        StartServer();
    }

    GRPCTestFixture::~GRPCTestFixture()
    {
        StopServer();
    }

    void GRPCTestFixture::StartServer()
    {
        // server_thread_ = std::thread([this]()
        //                              { run_server(); });
        run_server();

    }

    void GRPCTestFixture::StopServer()
    {
        int result = std::system("taskkill /F /IM PROJECT_INTEGRATION.exe");
        if (result != 0) {
            std::cerr << "Failed to execute taskkill. Error code: " << result << std::endl;
        }
        if (server_thread_.joinable())
        {
            server_thread_.join();
        }
    }

    energy::EnergyMeterServiceImpl &GRPCTestFixture::GetService()
    {
        return service;
    }
}