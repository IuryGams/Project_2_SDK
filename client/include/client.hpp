
#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "enums.hpp"

namespace energy
{
    class EnergyMeterClient
    {
    public:
        EnergyMeterClient(std::shared_ptr<grpc::Channel> channel);

        void CreateMeter(Lines line, const std::string &model);
        void ReadMeter(int id);
        void DeleteMeter(int id);
    };

    void RunClient();
}