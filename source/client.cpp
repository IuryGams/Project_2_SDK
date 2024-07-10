#include "client.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace energy
{

    EnergyMeterClient::EnergyMeterClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(EnergyMeter::NewStub(channel)) {}

    void EnergyMeterClient::CreateMeter(int id, Lines line, const std::string &model)
    {
        MeterInfor request;
        request.set_id(id);
        request.set_line(line);
        request.set_model(model);
        MeterInfor reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->CreateMeter(&context, request, &reply);
        if (status.ok())
        {
            std::cout << "Meter created: " << reply.id() << std::endl;
        }
        else
        {
            std::cout << "CreateMeter failed." << std::endl;
        }
    }

    void EnergyMeterClient::ReadMeter(int id)
    {
        MeterID request;
        request.set_id(id);
        MeterInfor reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->ReadMeter(&context, request, &reply);
        if (status.ok())
        {
            std::cout << "Meter read: " << reply.id() << " " << reply.model() << std::endl;
        }
        else
        {
            std::cout << "ReadMeter failed." << std::endl;
        }
    }

    void EnergyMeterClient::UpdateMeter(int id, Lines line, const std::string &model)
    {
        MeterInfor request;
        request.set_id(id);
        request.set_line(line);
        request.set_model(model);
        MeterInfor reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->UpdateMeter(&context, request, &reply);
        if (status.ok())
        {
            std::cout << "Meter updated: " << reply.id() << std::endl;
        }
        else
        {
            std::cout << "UpdateMeter failed." << std::endl;
        }
    }

    void EnergyMeterClient::DeleteMeter(int id)
    {
        MeterID request;
        request.set_id(id);
        Empty reply;
        grpc::ClientContext context;
        grpc::Status status = stub_->DeleteMeter(&context, request, &reply);
        if (status.ok())
        {
            std::cout << "Meter deleted." << std::endl;
        }
        else
        {
            std::cout << "DeleteMeter failed." << std::endl;
        }
    }

    int main(int argc, char **argv)
    {
        EnergyMeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

        client.CreateMeter(1, Lines::ARES, "Model-1");
        client.ReadMeter(1);
        client.UpdateMeter(1, Lines::APOLO, "Model-2");
        client.DeleteMeter(1);

        return 0;
    }

}