#include "energy_meter_services.hpp"
#include "operations.hpp"
#include "energy_meter.hpp"
#include "enums.hpp"

#include <vector>
#include <string>

namespace energy
{
    ees::Operations op;

    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext *context, const MeterInfor *request, MeterInfor *reply)
    {
        std::cout << "O medidor de energia foi criado!" << std::endl;
        *reply = *request;
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::ReadMeter(grpc::ServerContext *context, const MeterID *request, MeterInfor *reply)
    {
        std::cout << "Medidor de energia recebe um id: " << request->id() << std::endl;
        reply->set_id(request->id());
        reply->set_line(Lines::ARES);
        reply->set_model("Model-X");
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::UpdateMeter(grpc::ServerContext *context, const MeterInfor *request, MeterInfor *reply)
    {
        std::cout << "UpdateMeter request received with id: " << request->id() << std::endl;
        *reply = *request;
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::DeleteMeter(grpc::ServerContext *context, const MeterID *request, Empty *reply)
    {
        std::cout << "DeleteMeter request received with id: " << request->id() << std::endl;
        return grpc::Status::OK;
    }

}