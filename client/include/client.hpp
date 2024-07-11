
#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "enums.hpp"

namespace energy
{
    class EnergyMeterClient
    {
    public:
        EnergyMeterClient(std::shared_ptr<grpc::Channel> channel);

        void CreateMeter(int id, Lines line, const std::string &model);
        void ReadMeter(int id);
        void UpdateMeter(int id, Lines line, const std::string &model);
        void DeleteMeter(int id);
    };
}