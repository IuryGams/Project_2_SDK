#include "energy_meter_services.hpp"
#include "operations.hpp"
#include "energy_meter.hpp"
#include "enums.hpp"
#include "utils.hpp"

#include <vector>
#include <string>

namespace energy
{
    ees::Operations operations;

    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext *context, const MeterInfor *request, MeterCompleteInfor *reply)
    {
        ees::EnergyMeter new_meter(static_cast<ees::Lines>(request->line()), request->model());

        if (operations.add_new_model(new_meter))
        {
            reply->set_id(new_meter.get_id());
            reply->set_line(static_cast<Lines>(new_meter.get_line()));
            reply->set_model(new_meter.get_model());
            return grpc::Status::OK;
        }
        else
        {
            std::cout << "O medidor já existe e não foi adicionado." << std::endl;
            return grpc::Status(grpc::ALREADY_EXISTS, "Medidor já existe");
        }
    }

    grpc::Status EnergyMeterServiceImpl::ReadMeter(grpc::ServerContext *context, const MeterID *request, MeterCompleteInfor *reply)
    {
        auto found_meter = operations.find_meter_by_id(request->id());
        if (found_meter.get_id() == request->id())
        {
            reply->set_id(found_meter.get_id());
            reply->set_line(static_cast<Lines>(found_meter.get_line()));
            reply->set_model(found_meter.get_model());
            return grpc::Status::OK;
        }
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Medidor não encontrado no sistema");
    }

    grpc::Status EnergyMeterServiceImpl::GetAllMeters(grpc::ServerContext *context, const Empty *request, MeterListRequest *reply)
    {
        std::cout << "Solicitado a lista de medidores" << std::endl;

        std::vector<ees::EnergyMeter> list_meters = operations.get_meter_list();

        for (const auto &meter : list_meters)
        {
            MeterCompleteInfor *meter_info = reply->add_meters();
            meter_info->set_id(meter.get_id());
            meter_info->set_line(static_cast<Lines>(meter.get_line()));
            meter_info->set_model(meter.get_model());
        }

        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::DeleteMeter(grpc::ServerContext *context, const MeterID *request, ResponseStatus *reply)
    {
        if (operations.remove_model(request->id()))
        {
            reply->set_status(ResponseStatus::COMMAND_EXECUTION_SUCCESSFUL);
            return grpc::Status::OK;
        }
        reply->set_status(ResponseStatus::COMMAND_EXECUTION_FAILED);

        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::GetAllLines(grpc::ServerContext *context, const Empty *request, AllLinesRequest *reply)
    {
        auto lines = operations.get_all_lines();

        // for(auto const &line : lines)
        // {
        //     AllLinesRequest *lines_infor = reply->add_lines();
        //     lines_infor->set_lines(static_cast<Lines>(line));

        // }
        return grpc::Status::OK;
    }

}