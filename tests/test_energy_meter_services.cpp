#pragma once
#include "catch.hpp"
#include "energy_meter.grpc.pb.h"
#include "energy_meter_services.hpp"
#include "energy_meter.hpp"
#include "utils.hpp"
#include "operations.hpp"
#include "project_exceptions.hpp"
#include <grpcpp/grpcpp.h>

ees::Operations operations;

TEST_CASE("CreateMeter Test", "[create_meter]") // Testing OK
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    ees::Operations op;

    grpc::ServerContext context;
    MeterCompleteInfor request;
    MeterCompleteInfor reply;

    SECTION("Successfully create a new meter")
    {

        request.set_id(20);
        request.set_line(Lines::ARES);
        request.set_model("Modelo exemplo");

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        if (op.add_new_model({request.id(), static_cast<ees::Lines>(request.line()), request.model()}))
        {
            REQUIRE(reply.id() == request.id());
            REQUIRE(reply.line() == request.line());
            REQUIRE(reply.model() == request.model());
            REQUIRE(status.ok());
        }
    }

    SECTION("Meter already exists")
    {
        request.set_id(1);
        request.set_line(Lines::ARES);
        request.set_model("Modelo exemplo");

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(grpc::StatusCode::ALREADY_EXISTS);
        REQUIRE(status.error_message() == "Medidor já existe.");
    }
}

TEST_CASE("ReadMeter", "[read_meter]")
{
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    MeterID request;
    MeterCompleteInfor reply;

    SECTION("Success - Meter Found")
    {
        request.set_id(3);

        // grpc::Status status = service.ReadMeter(&context, &request, &reply);

        REQUIRE(reply.id() == request.id());
    }

    SECTION("NotFound - Meter Not Found")
    {
        request.set_id(9999);

        // REQUIRE_THROWS_AS(service.ReadMeter(&context, &request, &reply), ees::InternalServerErrorThisMeterAlreadyExist);
    }
}

TEST_CASE("GetAllMeters returns the list of meters", "[all_meters]")
{
    ees::Operations op;
    std::vector<ees::EnergyMeter> meter_list = op.get_meter_list();
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    Empty request;
    MeterListReply reply;

    grpc::Status status = service.GetAllMeters(&context, &request, &reply);

    REQUIRE(reply.meters_size() > 0);

    for (size_t i = 0; i < reply.meters_size(); i++)
    {
        const MeterCompleteInfor &meter_info = reply.meters(i);

        REQUIRE(meter_info.id() == meter_list.at(i).get_id());
        REQUIRE(meter_info.line() == ees::convert_enum_cpp_to_proto_enum(meter_list.at(i).get_line()));
        REQUIRE(meter_info.model() == meter_list.at(i).get_model());
    }
}

TEST_CASE("DeleteMeter removes the meter and returns success", "[delete_meter]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    MeterID request;
    ResponseStatus reply;

    SECTION("Request Successful")
    {
        // Assuming there's a meter with ID 2
        request.set_id(2);

        // Test
        auto status = service.DeleteMeter(&context, &request, &reply);

        // Verify
        if (status.ok())
        {
            REQUIRE(reply.status() == ResponseStatus::COMMAND_EXECUTION_SUCCESSFUL);
        }
    }

    SECTION("Request Failed")
    {
        // Assuming there's a meter with ID 999
        request.set_id(999);

        // Test
        auto status = service.DeleteMeter(&context, &request, &reply);

        // Verify
        REQUIRE(reply.status() == ResponseStatus::COMMAND_EXECUTION_FAILED);
    }
}

TEST_CASE("GetAllLines returns all available lines", "[all_lines]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    Empty request;
    AllLinesReply reply;

    // Test
    auto status = service.GetAllLines(&context, &request, &reply);

    // Verify
    REQUIRE(status.ok());
    REQUIRE(reply.lines_size() == 4);
    REQUIRE(reply.lines(0) == Lines::ARES);
    REQUIRE(reply.lines(1) == Lines::APOLO);
    REQUIRE(reply.lines(2) == Lines::CRONOS);
    REQUIRE(reply.lines(3) == Lines::ZEUS);
}

TEST_CASE("GetModelsByLine returns models for a given line", "[]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    RequestMeterLine request;
    MeterListReply reply;

    // Assuming there's a line called "ARES"
    request.set_meter_line("ARES");

    // Test
    auto status = service.GetModelsByLine(&context, &request, &reply);

    // Verify
    REQUIRE(status.ok());
    REQUIRE(reply.meters_size() > 0);
    for (int i = 0; i < reply.meters_size(); ++i)
    {
        const auto &meter = reply.meters(i);
        REQUIRE(meter.line() == Lines::ARES);
        REQUIRE_FALSE(meter.model().empty());
    }
}