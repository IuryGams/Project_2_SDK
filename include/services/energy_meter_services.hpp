#pragma once

#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "operations.hpp"

namespace energy
{
    class EnergyMeterServiceImpl final : public EnergyMeter::Service
    {
    public:
        grpc::Status CreateMeter(
            grpc::ServerContext *context, const MeterInfor *request, MeterInfor *reply) override;

        grpc::Status ReadMeter(
            grpc::ServerContext *context, const MeterID *request, MeterInfor *reply) override;

        grpc::Status UpdateMeter(
            grpc::ServerContext *context, const MeterInfor *request, MeterInfor *reply) override;

        grpc::Status DeleteMeter(
            grpc::ServerContext *context, const MeterID *request, Empty *reply) override;

    private:
        std::unique_ptr<EnergyMeter::Stub> stub_;
        ees::Operations operations_;
    };
}

