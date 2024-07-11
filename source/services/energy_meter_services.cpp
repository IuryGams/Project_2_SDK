#include "energy_meter_services.hpp"
#include "operations.hpp"
#include "energy_meter.hpp"
#include "enums.hpp"
#include "utils.hpp"

#include <vector>
#include <string>

namespace energy
{

    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext* context, const MeterInfor* request, MeterInfor* reply) {

        ees::EnergyMeter new_meter(static_cast<ees::Lines>(request->line()), request->model());

    if (operations_.add_new_model(new_meter)) {
        std::cout << "O medidor de energia foi criado e adicionado à lista!" << std::endl;
        std::string line = ees::convert_enumline_to_string(new_meter.get_line());

        reply->set_id(new_meter.get_id());
        // reply->set_line(new_meter.get_line());
        reply->set_model(new_meter.get_model()); 
        return grpc::Status::OK;
    } else {
        std::cout << "O medidor já existe e não foi adicionado." << std::endl;
        return grpc::Status(grpc::ALREADY_EXISTS, "Medidor já existe");
    }
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