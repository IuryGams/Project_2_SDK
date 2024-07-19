#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"

namespace energy
{
    class EnergyMeterClient
    {
    public:
        EnergyMeterClient(std::shared_ptr<grpc::Channel> channel);

        bool CreateMeter(int id, int line, const std::string &model);
        bool ReadMeter(int id);
        void GetAllMeters();
        bool DeleteMeter(int id);
        void GetAllLines();
        void GetModelsByLine(std::string line);

    private:
        std::unique_ptr<EnergyMeter::Stub> stub_;
    };
}