#pragma once

#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include <iostream>
#include <memory>
#include <string>
#include "enums.hpp"

namespace energy
{
    class EnergyMeterClient
    {
        public:
        EnergyMeterClient(std::shared_ptr<grpc::Channel> channel);
        MeterCompleteInfor CreateMeter(const MeterCompleteInfor &meter);
        MeterCompleteInfor ReadMeter(const MeterID &meter_id);
        void DeleteMeter(const MeterID &meter_id);

        private:
        std::unique_ptr<EnergyMeter::Stub> stub_;
            
    };
}