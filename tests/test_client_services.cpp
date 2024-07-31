#pragma once
#include "catch.hpp"
#include "client_method.hpp"
#include "project_exceptions.hpp"
#include "GRPCTestFixture.hpp"
#include "utils.hpp"
#include "client.hpp"
#include "server.hpp"

#include <thread>

namespace test

{

    TEST_CASE_METHOD(GRPCTestFixture, "Testing create meter request client", "[client_grpc]")
    {
        MeterCompleteInfo request; // Type of Request
        CreateMeterReply reply;    // Type of Response
        grpc::ClientContext context;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        SECTION("Create a new meter successfully")
        {
            // Configure request
            request.set_id(18);
            request.set_line(::Lines::ARES);
            request.set_model("Test Model");

            // Send request
            grpc::Status status = stub->CreateMeter(&context, request, &reply);

            // Verify response
            REQUIRE(status.ok());
            REQUIRE(reply.has_meter());
            REQUIRE(reply.meter().id() == request.id());
            REQUIRE(reply.meter().line() == request.line());
            REQUIRE(reply.meter().model() == request.model());
        }

        SECTION("Fail to create a meter that already exists")
        {
            // Configure request
            request.set_id(17);
            request.set_line(::Lines::ARES);
            request.set_model("Test Model");

            // Send request to ensure the meter is created
            grpc::Status status = stub->CreateMeter(&context, request, &reply);

            REQUIRE(status.ok());
            REQUIRE(reply.has_error());
            REQUIRE(reply.error() == ReplyStatusException::ALREADY_EXISTS_METER);
        }

        SECTION("Fail to create a meter with a non-existing line")
        {
            // Configure request
            request.set_id(18);
            request.set_line(::Lines::UNKNOWN);
            request.set_model("Model UNKNOWN");

            // Send request
            grpc::Status status = stub->CreateMeter(&context, request, &reply);

            REQUIRE(status.ok());
            REQUIRE(reply.has_error());
            REQUIRE(reply.error() == ReplyStatusException::NOT_EXISTS_LINE);
        }
    }

    TEST_CASE_METHOD(GRPCTestFixture, "Testing request client GetAllMeters", "[client_grpc]")
    {
        ees::Operations operations;
        grpc::ClientContext context;
        Empty request;
        MeterListReply reply;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        SECTION("Get all meters successfully")
        {
            grpc::Status status = stub->GetAllMeters(&context, request, &reply);
            std::vector<ees::EnergyMeter> meter_list = operations.get_meter_list();

            REQUIRE(status.ok());
            REQUIRE(reply.meters_size() == meter_list.size());

            for (int i = 0; i < reply.meters_size(); ++i)
            {
                const auto &meter_reply = reply.meters(i);
                const auto &meter = meter_list.at(i);

                REQUIRE(meter_reply.id() == meter.get_id());
                REQUIRE(meter_reply.line() == static_cast<::Lines>(ees::convert_enum_cpp_to_proto_enum(meter.get_line())));
                REQUIRE(meter_reply.model() == meter.get_model());
            }
        }
    }

    TEST_CASE_METHOD(GRPCTestFixture, "Testing Read meter request client", "[client_grpc]")
    {
        grpc::ClientContext context;
        MeterID request;
        ReadMeterReply reply;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        SECTION("Success - Meter Found")
        {
            request.set_id(1);

            grpc::Status status = stub->ReadMeter(&context, request, &reply);

            REQUIRE(status.ok());
            REQUIRE(reply.has_meter());
            REQUIRE(reply.meter().id() == 1);
            REQUIRE(reply.meter().line() == ::Lines::ARES);
            REQUIRE(reply.meter().model() == "7021");
        }

        SECTION("NotFound - Meter Not Found")
        {
            request.set_id(9999);
            grpc::Status status = stub->ReadMeter(&context, request, &reply);

            REQUIRE(status.ok());
            REQUIRE(reply.has_error());
            REQUIRE(reply.error() == ReplyStatusException::NOT_FOUND);
        }
    }

    TEST_CASE_METHOD(GRPCTestFixture, "Testing delete meter client request", "[client_grpc]")
    {
        grpc::ClientContext context;
        MeterID request;
        ResponseStatus reply;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        SECTION("Request Successful")
        {
            // Assuming there's a meter with ID 18
            request.set_id(17);

            // Test
            auto status = stub->DeleteMeter(&context, request, &reply);

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
            auto status = stub->DeleteMeter(&context, request, &reply);

            // Verify
            REQUIRE(reply.status() == ResponseStatus::COMMAND_EXECUTION_FAILED);
        }
    }

    TEST_CASE_METHOD(GRPCTestFixture, "Testing GetAllLines request client", "[client_grpc]")
    {
        // Setup
        grpc::ClientContext context;
        Empty request;
        AllLinesReply reply;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        // Test
        auto status = stub->GetAllLines(&context, request, &reply);

        // Verify
        REQUIRE(status.ok());
        REQUIRE(reply.lines_size() == 4);
        REQUIRE(reply.lines(0) == Lines::ARES);
        REQUIRE(reply.lines(1) == Lines::APOLO);
        REQUIRE(reply.lines(2) == Lines::CRONOS);
        REQUIRE(reply.lines(3) == Lines::ZEUS);
    }

    TEST_CASE_METHOD(GRPCTestFixture, "Testing GetModelsByLine client request", "[client_grpc]")
    {
        // Setup
        grpc::ClientContext context;
        RequestMeterLine request;
        MeterListReply reply;

        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        auto stub = EnergyMeter::NewStub(channel);

        SECTION("returns successful list meter")
        {
            request.set_meter_line("ARES");

            // Test
            auto status = stub->GetModelsByLine(&context, request, &reply);

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

        SECTION("throw exception with no line exists")
        {
            request.set_meter_line("Kratos");

            // Test
            auto status = stub->GetModelsByLine(&context, request, &reply);

            // Verify
            REQUIRE(status.ok());
            REQUIRE(reply.has_error());
            REQUIRE(reply.error() == ReplyStatusException::NOT_EXISTS_LINE);
        }
    }

}