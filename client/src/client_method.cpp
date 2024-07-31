#include "client_method.hpp"
#include "enums.hpp"
#include "utils.hpp"
#include "operations.hpp"
#include "project_exceptions.hpp"

namespace energy
{

    EnergyMeterClient::EnergyMeterClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(EnergyMeter::NewStub(channel)) {};

    // CreateMeter
    bool EnergyMeterClient::CreateMeter(int id, int line, const std::string &model)
    {
        MeterCompleteInfo request;
        request.set_id(id);
        request.set_line(static_cast<Lines>(line));
        request.set_model(model);

        CreateMeterReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->CreateMeter(&context, request, &reply);
        if (status.ok())
        {
            if (reply.has_meter())
            {
                std::cout << "O medidor foi criado com o ID: " << reply.meter().id() << std::endl;
                return true;
            }
            else
            {
                std::cout << "Error: " << reply.error() << std::endl;
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
        return false;
    }

    // ReadMeter
    bool EnergyMeterClient::ReadMeter(int id)
    {
        MeterID request;
        request.set_id(id);

        ReadMeterReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->ReadMeter(&context, request, &reply);
        if (status.ok())
        {
            if (reply.has_meter())
            {
                std::cout << "ID: " << reply.meter().id() << std::endl;
                std::cout << "Linha: " << reply.meter().line() << std::endl;
                std::cout << "Modelo: " << reply.meter().model() << std::endl;
                return true;
            }
            else
            {
                std::cout << "Erro: " << reply.error() << std::endl;
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
        return false;
    }

    // GetAllMeters
    std::vector<MeterCompleteInfo> EnergyMeterClient::GetAllMeters()
    {
        Empty request;
        MeterListReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->GetAllMeters(&context, request, &reply);

        std::vector<MeterCompleteInfo> meters_reply;

        if (status.ok())
        {
            for (const auto &meter : reply.meters())
            {
                meters_reply.push_back(meter);
            }
            return meters_reply;
        }
        return meters_reply;
    }

    // DeleteMeter
    bool EnergyMeterClient::DeleteMeter(int id)
    {
        MeterID request;
        request.set_id(id);

        ResponseStatus reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->DeleteMeter(&context, request, &reply);
        if (status.ok())
        {
            std::cout << "Delete status: " << reply.status() << std::endl;
            return true;
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
        return false;
    }

    // GetAllLines
    void EnergyMeterClient::GetAllLines()
    {
        Empty request;
        AllLinesReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->GetAllLines(&context, request, &reply);
        if (status.ok())
        {
            for (const auto &line : reply.lines())
            {
                std::cout << "Line: " << ees::convert_enumline_to_string(ees::convert_proto_enum_to_cpp_enum(line)) << std::endl;
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }

    // GetModelsByLine
    void EnergyMeterClient::GetModelsByLine(const std::string &line)
    {
        RequestMeterLine request;
        request.set_meter_line(line);

        MeterListReply reply;
        grpc::ClientContext context;

        grpc::Status status = stub_->GetModelsByLine(&context, request, &reply);
        if (status.ok())
        {
            for (const auto &meter : reply.meters())
            {
                std::cout << "Meter ID: " << meter.id() << ", Line: " << meter.line() << ", Model: " << meter.model() << std::endl;
            }
        }
        else
        {
            std::cout << "RPC failed" << std::endl;
        }
    }
}