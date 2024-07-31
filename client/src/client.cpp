#include "enums.hpp"
#include "utils.hpp"
#include "client.hpp"

namespace energy
{
    auto Client::CreateClient() -> std::unique_ptr<EnergyMeter::Stub>
    {
        std::string localhost = "localhost:50051";
        auto channel = grpc::CreateChannel(localhost, grpc::InsecureChannelCredentials());
        return EnergyMeter::NewStub(channel);
    }

}