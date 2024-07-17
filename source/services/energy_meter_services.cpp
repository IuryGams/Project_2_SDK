#include "energy_meter_services.hpp"
#include "operations.hpp"
#include "energy_meter.hpp"
#include "enums.hpp"
#include "utils.hpp"
#include "project_exceptions.hpp"

#include <vector>
#include <string>

namespace energy
{
    ees::Operations operations;

    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext *context, const MeterCompleteInfor *request, MeterCompleteInfor *reply)
    {
        try
        {
            ees::EnergyMeter new_meter(request->id(), static_cast<ees::Lines>(request->line()), request->model());

            if (operations.add_new_model(new_meter))
            {
                reply->set_id(new_meter.get_id());
                reply->set_line(static_cast<Lines>(new_meter.get_line()));
                reply->set_model(new_meter.get_model());
            }
            return grpc::Status::OK;
        }
        catch (const ees::NotFound)
        {
            return grpc::Status(grpc::ALREADY_EXISTS, "Medidor já existe.");
        }
    }

    grpc::Status EnergyMeterServiceImpl::ReadMeter(grpc::ServerContext *context, const MeterID *request, ReadMeterReply *reply)
    {
        try
        {
            ees::EnergyMeter found_meter = operations.find_meter_by_id(static_cast<int>(request->id()));

            reply->mutable_meter()->set_id(found_meter.get_id());
            reply->mutable_meter()->set_line(static_cast<Lines>(found_meter.get_line()));
            reply->mutable_meter()->set_model(found_meter.get_model());
            return grpc::Status::OK;
        }
        catch (const ees::NotFound)
        {
            reply->set_response(ReplyStatusException::NOT_FOUND);
            return grpc::Status::OK;
        }
    }

    grpc::Status EnergyMeterServiceImpl::GetAllMeters(grpc::ServerContext *context, const Empty *request, MeterListReply *reply)
    {
        std::vector<ees::EnergyMeter> list_meters = operations.get_meter_list();

        for (const auto &meter : list_meters)
        {
            MeterCompleteInfor *meter_info = reply->add_meters();
            meter_info->set_id(meter.get_id());
            meter_info->set_line(static_cast<::Lines>(convert_enum_cpp_to_proto_enum(meter.get_line())));
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

    grpc::Status EnergyMeterServiceImpl::GetAllLines(grpc::ServerContext *context, const Empty *request, AllLinesReply *reply)
    {

        // Limpa qualquer dado pré-existente em reply
        reply->clear_lines();

        // Adiciona todas as linhas disponíveis de acordo com o enum Lines
        reply->add_lines(Lines::ARES);
        reply->add_lines(Lines::APOLO);
        reply->add_lines(Lines::CRONOS);
        reply->add_lines(Lines::ZEUS);

        // Retorna Status OK para indicar sucesso na operação
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::GetModelsByLine(grpc::ServerContext *context, const RequestMeterLine *request, MeterListReply *reply)
    {
        auto models = operations.filter_by_line(ees::to_uppercase(request->meter_line()));

        for (const auto &model : models)
        {
            auto *meter_infor = reply->add_meters();
            meter_infor->set_id(model.get_id());
            meter_infor->set_line(static_cast<Lines>(model.get_line()));
            meter_infor->set_model(model.get_model());
        }

        return grpc::Status::OK;
    }

}
