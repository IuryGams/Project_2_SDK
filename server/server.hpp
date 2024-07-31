#pragma once
#include "energy_meter_services.hpp"
#include <grpcpp/grpcpp.h>
#include <memory>

namespace energy
{

    class Server
    {
        public:
            void RunServer();
            void StopServer();
        private:
            std::unique_ptr<grpc::Server> server_;
            energy::EnergyMeterServiceImpl service_;
    };

} // namespace energy
