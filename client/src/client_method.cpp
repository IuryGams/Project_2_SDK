#include "client_method.hpp"

namespace energy
{

    EnergyMeterClient::EnergyMeterClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(EnergyMeter::NewStub(channel)) {};

    MeterCompleteInfor EnergyMeterClient::CreateMeter(const MeterCompleteInfor &meter)
    {
        MeterCompleteInfor response;
        grpc::ClientContext context;
        grpc::Status status = stub_->CreateMeter(&context, meter, &response);
        if (status.ok())
        {
            return response;
        }
        else
        {
            std::cerr << "CreateMeter RPC failed." << std::endl;
            return MeterCompleteInfor();
        }
    }

    // MeterCompleteInfor EnergyMeterClient::ReadMeter(const MeterID &meter_id)
    // {
    //     MeterCompleteInfor response;
    //     grpc::ClientContext context;
    //     grpc::Status status = stub_->ReadMeter(&context, meter_id, &response);
    //     if (status.ok())
    //     {
    //         return response;
    //     }
    //     else
    //     {
    //         std::cerr << "ReadMeter RPC failed." << std::endl;
    //         return MeterCompleteInfor();
    //     }
    // }

    void EnergyMeterClient::DeleteMeter(const MeterID &meter_id)
    {
        ResponseStatus response;
        grpc::ClientContext context;
        grpc::Status status = stub_->DeleteMeter(&context, meter_id, &response);
        if (status.ok())
        {
            std::cout << "DeleteMeter tudo correto! confia!." << std::endl;
        }
        else
        {
            std::cerr << "DeleteMeter RPC failed." << std::endl;
        }
    }
}