#pragma once
#include "server.hpp"
#include "energy_meter_services.hpp"
#include <thread>

namespace test
{
    class GRPCTestFixture
    {
        public:
            GRPCTestFixture();
            ~GRPCTestFixture();
            energy::EnergyMeterServiceImpl &GetService();

        private:
            void StartServer();
            void StopServer();

            energy::Server server_;
            std::thread server_thread_;
            energy::EnergyMeterServiceImpl service;
    };
}