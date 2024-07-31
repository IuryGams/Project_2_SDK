#pragma once

#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"
#include "operations.hpp"

namespace energy
{
    class EnergyMeterServiceImpl final : public EnergyMeter::Service
    {
    public:
        // Okay
        grpc::Status CreateMeter(
            grpc::ServerContext *context, const MeterCompleteInfo *request, CreateMeterReply *reply) override;
        // Okay
        grpc::Status GetAllMeters(
            grpc::ServerContext *context, const Empty *request, MeterListReply *reply) override;
        // Okay
        grpc::Status ReadMeter(
            grpc::ServerContext *context, const MeterID *request, ReadMeterReply *reply) override; 
        // Okay
        grpc::Status DeleteMeter(
            grpc::ServerContext *context, const MeterID *request, ResponseStatus *reply) override;

        grpc::Status GetAllLines(
            grpc::ServerContext *context, const Empty *request, AllLinesReply *reply ) override;

        grpc::Status GetModelsByLine(
            grpc::ServerContext *context, const RequestMeterLine *Request, MeterListReply *reply) override;
    };
}

