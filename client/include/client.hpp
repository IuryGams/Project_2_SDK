
#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "enums.hpp"

namespace energy
{
    class Client
    {
    public:
        auto CreateClient() -> std::unique_ptr<EnergyMeter::Stub>;
    };

}