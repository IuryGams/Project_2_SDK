
#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "enums.hpp"

namespace energy
{
    class EnergyMeterClient
    {
    public:
        EnergyMeterClient(std::shared_ptr<grpc::Channel> channel);
    };

    void RunClient();
}