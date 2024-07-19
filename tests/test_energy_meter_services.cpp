#pragma once
#include "catch.hpp"
#include "energy_meter.grpc.pb.h"
#include "energy_meter_services.hpp"
#include "energy_meter.hpp"
#include "utils.hpp"
#include "operations.hpp"
#include "project_exceptions.hpp"
#include <grpcpp/grpcpp.h>


TEST_CASE("GetAllMeters returns the list of meters", "[all_meters]")
{
    ees::Operations operations;
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    Empty request;
    MeterListReply reply;

    SECTION("Get all meters successfully")
    {
        grpc::Status status = service.GetAllMeters(&context, &request, &reply);
        std::vector<ees::EnergyMeter> meter_list = operations.get_meter_list();

        REQUIRE(status.ok());
        REQUIRE(reply.meters_size() == meter_list.size());

        for (int i = 0; i < reply.meters_size(); ++i)
        {
            const auto &meter_reply = reply.meters(i);
            const auto &meter = meter_list[i];

            REQUIRE(meter_reply.id() == meter.get_id());
            REQUIRE(meter_reply.line() == static_cast<::Lines>(convert_enum_cpp_to_proto_enum(meter.get_line())));
            REQUIRE(meter_reply.model() == meter.get_model());
        }
    }
}

TEST_CASE("CreateMeter Test", "[create_meter]") // Testing OK
{
    // Setup
    ees::Operations operations;
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    MeterCompleteInfor request;
    CreateMeterReply reply;

    SECTION("Create a new meter successfully")
    {
        request.set_id(18);
        request.set_line(::Lines::ARES);
        request.set_model("Model test");

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.has_meter());
        REQUIRE(reply.meter().id() == request.id());
        REQUIRE(reply.meter().line() == request.line());
        REQUIRE(reply.meter().model() == request.model());
    }

    SECTION("Fail to create a meter that already exists")
    {
        request.set_id(1);
        request.set_line(::Lines::ARES);
        request.set_model("Model test already exists");

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.has_error());
        REQUIRE(reply.error() == ReplyStatusException::ALREADY_EXISTS_METER);
    }

    SECTION("Fail to create a meter with a non-existing line")
    {
        request.set_id(19);
        request.set_line(::Lines::UNKNOWN);
        request.set_model("Model UNKNOWN");

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.has_error());
        REQUIRE(reply.error() == ReplyStatusException::NOT_EXISTS_LINE);
    }
}

TEST_CASE("ReadMeter", "[read_meter]")
{
    energy::EnergyMeterServiceImpl service;
    ees::Operations operations;
    grpc::ServerContext context;
    MeterID request;
    ReadMeterReply reply;

    SECTION("Success - Meter Found")
    {
        request.set_id(1);

        grpc::Status status = service.ReadMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.has_meter());
        REQUIRE(reply.meter().id() == 1);
        REQUIRE(reply.meter().line() == ::Lines::ARES);
        REQUIRE(reply.meter().model() == "7021");
    }

    SECTION("NotFound - Meter Not Found")
    {
        request.set_id(9999);
        grpc::Status status = service.ReadMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.has_error());
        REQUIRE(reply.error() == ReplyStatusException::NOT_FOUND);
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

TEST_CASE("GetModelsByLine returns models for a given line", "[get_model]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    RequestMeterLine request;
    MeterListReply reply;

    SECTION("returns successful list meter")
    {
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

    SECTION("throw expection with no line exists")
    {
        request.set_meter_line("Kratos");

        // Test
        auto status = service.GetModelsByLine(&context, &request, &reply);

        // Verify
        REQUIRE(status.ok());
        REQUIRE(reply.has_error());
        REQUIRE(reply.error() == ReplyStatusException::NOT_EXISTS_LINE);
    }
}