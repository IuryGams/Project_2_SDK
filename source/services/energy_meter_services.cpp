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
    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext *context, const MeterCompleteInfo *request, CreateMeterReply *reply)
    {
        try
        {
            ees::EnergyMeter new_meter(request->id(), static_cast<ees::Lines>(request->line()), request->model());

            ees::Operations::add_new_model(new_meter);

            reply->mutable_meter()->set_id(new_meter.get_id());
            reply->mutable_meter()->set_line(static_cast<Lines>(new_meter.get_line()));
            reply->mutable_meter()->set_model(new_meter.get_model());
            return grpc::Status::OK;
        }
        catch (const exceptions::AlreadyExists)
        {
            reply->set_error(ReplyStatusException::ALREADY_EXISTS_METER);
            return grpc::Status::OK;
        }
        catch (const exceptions::NotExists)
        {
            reply->set_error(ReplyStatusException::NOT_EXISTS_LINE);
            return grpc::Status::OK;
        }
    }

    grpc::Status EnergyMeterServiceImpl::ReadMeter(grpc::ServerContext *context, const MeterID *request, ReadMeterReply *reply)
    {
        try
        {
            ees::EnergyMeter found_meter = ees::Operations::find_meter_by_id(static_cast<int>(request->id()));

            reply->mutable_meter()->set_id(found_meter.get_id());
            reply->mutable_meter()->set_line(static_cast<Lines>(found_meter.get_line()));
            reply->mutable_meter()->set_model(found_meter.get_model());

            return grpc::Status::OK;
        }
        catch (const exceptions::NotFound &)
        {
            reply->set_error(ReplyStatusException::NOT_FOUND);
            return grpc::Status::OK;
        }
    }

    grpc::Status EnergyMeterServiceImpl::GetAllMeters(grpc::ServerContext *context, const Empty *request, MeterListReply *reply)
    {
        std::vector<ees::EnergyMeter> list_meters = ees::Operations::get_meter_list();

        for (const auto &meter : list_meters)
        {
            MeterCompleteInfo *meter_info = reply->add_meters();
            meter_info->set_id(meter.get_id());
            meter_info->set_line(static_cast<::Lines>(convert_enum_cpp_to_proto_enum(meter.get_line())));
            meter_info->set_model(meter.get_model());
        }
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::DeleteMeter(grpc::ServerContext *context, const MeterID *request, ResponseStatus *reply)
    {
        try
        {
            if (ees::Operations::remove_model(request->id()))
            {
                reply->set_status(ResponseStatus::COMMAND_EXECUTION_SUCCESSFUL);
            }
            return grpc::Status::OK;
        }
        catch (const std::exception &e)
        {
            reply->set_status(ResponseStatus::COMMAND_EXECUTION_FAILED);
            return grpc::Status::OK;
        }
    }

    grpc::Status EnergyMeterServiceImpl::GetAllLines(grpc::ServerContext *context, const Empty *request, AllLinesReply *reply)
    {
        reply->clear_lines();

        reply->add_lines(Lines::ARES);
        reply->add_lines(Lines::APOLO);
        reply->add_lines(Lines::CRONOS);
        reply->add_lines(Lines::ZEUS);

        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::GetModelsByLine(grpc::ServerContext *context, const RequestMeterLine *request, MeterListReply *reply)
    {
        try
        {
            auto models = ees::Operations::filter_by_line(request->meter_line());

            for (const auto &model : models)
            {
                auto *meter_info = reply->add_meters();
                meter_info->set_id(model.get_id());
                meter_info->set_line(static_cast<Lines>(model.get_line()));
                meter_info->set_model(model.get_model());
            }
            return grpc::Status::OK;
        }
        catch (const exceptions::NotExists)
        {
            reply->set_error(ReplyStatusException::NOT_EXISTS_LINE);
            return grpc::Status::OK;
        }
    }

}
