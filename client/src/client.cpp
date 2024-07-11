#include <iostream>
#include <memory>
#include <string>
#include "enums.hpp"

#include <grpcpp/grpcpp.h>
#include "energy_meter.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class EnergyMeterClient
{
public:
    EnergyMeterClient(std::shared_ptr<Channel> channel)
        : stub_(EnergyMeter::NewStub(channel)) {}

    MeterInfor CreateMeter(const MeterInfor &meter)
    {
        MeterInfor response;
        ClientContext context;
        Status status = stub_->CreateMeter(&context, meter, &response);
        if (status.ok())
        {
            return response;
        }
        else
        {
            std::cerr << "CreateMeter RPC failed." << std::endl;
            return MeterInfor();
        }
    }

    MeterInfor ReadMeter(const MeterID &meter_id)
    {
        MeterInfor response;
        ClientContext context;
        Status status = stub_->ReadMeter(&context, meter_id, &response);
        if (status.ok())
        {
            return response;
        }
        else
        {
            std::cerr << "ReadMeter RPC failed." << std::endl;
            return MeterInfor();
        }
    }

    MeterInfor UpdateMeter(const MeterInfor &meter)
    {
        MeterInfor response;
        ClientContext context;
        Status status = stub_->UpdateMeter(&context, meter, &response);
        if (status.ok())
        {
            return response;
        }
        else
        {
            std::cerr << "UpdateMeter RPC failed." << std::endl;
            return MeterInfor();
        }
    }

    void DeleteMeter(const MeterID &meter_id)
    {
        Empty response;
        ClientContext context;
        Status status = stub_->DeleteMeter(&context, meter_id, &response);
        if (status.ok())
        {
            std::cout << "DeleteMeter succeeded." << std::endl;
        }
        else
        {
            std::cerr << "DeleteMeter RPC failed." << std::endl;
        }
    }

private:
    std::unique_ptr<EnergyMeter::Stub> stub_;
};

int main(int argc, char **argv)
{
    EnergyMeterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    MeterInfor meter;
    meter.set_id(1);
    meter.set_line(Lines::ARES);
    meter.set_model("Model X");

    MeterInfor response = client.CreateMeter(meter);
    std::cout << "CreateMeter response: " << response.model() << std::endl;

    MeterID meter_id;
    meter_id.set_id(1);
    response = client.ReadMeter(meter_id);
    std::cout << "ReadMeter response: " << response.model() << std::endl;

    response.set_model("Model Y");
    response = client.UpdateMeter(response);
    std::cout << "UpdateMeter response: " << response.model() << std::endl;

    client.DeleteMeter(meter_id);

    return 0;
}
