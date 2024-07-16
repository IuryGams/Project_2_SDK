#pragma once
#include "catch.hpp"
#include "energy_meter.grpc.pb.h"
#include "energy_meter_services.hpp"
#include "energy_meter.hpp"
#include <grpcpp/grpcpp.h>
#include "operations.hpp"

ees::Operations operations;

TEST_CASE("CreateMeter Test", "[grpc]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    MeterInfor request;
    MeterCompleteInfor reply;

    // Defina os valores apropriados para a linha e o modelo
    request.set_line(Lines::ARES); 
    request.set_model("Modelo exemplo");

    SECTION("Successfully create a new meter")
    {
        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.id() != 0); // Verifique se o ID foi definido corretamente
        REQUIRE(reply.line() == request.line());
        REQUIRE(reply.model() == request.model());
    }

    SECTION("Meter already exists")
    {
        // Adicione um medidor existente na lista
        ees::EnergyMeter existing_meter(static_cast<ees::Lines>(request.line()), request.model());
        operations.add_new_model(existing_meter);

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.error_code() == grpc::ALREADY_EXISTS);
        REQUIRE(status.error_message() == "Medidor já existe");
    }
}

TEST_CASE("ReadMeter", "[ReadMeter]")
{
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    MeterCompleteInfor reply;

    SECTION("Success - Meter Found")
    {
        MeterID request;
        request.set_id(3);

        grpc::Status status = service.ReadMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.id() == 3);
        // Adicione mais verificações conforme necessário para os outros campos do reply
    }

    SECTION("NotFound - Meter Not Found")
    {
        MeterID request;
        request.set_id(9999);

        grpc::Status status = service.ReadMeter(&context, &request, &reply);

        REQUIRE(status.error_code() == grpc::StatusCode::NOT_FOUND);
        // Verifica a mensagem de erro, se necessário
        REQUIRE(status.error_message() == "Medidor de energia não encontrado.");
    }

    // Adicione mais SECTIONS conforme necessário para outros casos de teste
}

TEST_CASE("GetAllMeters returns the list of meters", "[EnergyMeterServiceImpl]")
{
    // Instanciação do serviço real
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    Empty request;
    MeterListRequest reply;

    grpc::Status status = service.GetAllMeters(&context, &request, &reply);

    REQUIRE(status.ok());

    REQUIRE(reply.meters_size() > 0); // Verifique se há medidores na lista

    for (int i = 0; i < reply.meters_size(); ++i)
    {

        const auto &meter = reply.meters(i);
        REQUIRE(meter.id() != 0);
        REQUIRE(meter.line() != ::Lines::UNKNOWN); // Certifique-se de que a linha é válida
        REQUIRE_FALSE(meter.model().empty());
    }
}

TEST_CASE("DeleteMeter removes the meter and returns success", "[EnergyMeterServiceImpl]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    MeterID request;
    ResponseStatus reply;

    // Assuming there's a meter with ID 1
    request.set_id(1);

    // Test
    auto status = service.DeleteMeter(&context, &request, &reply);

    // Verify
    REQUIRE(status.ok());
    REQUIRE(reply.status() == ResponseStatus::COMMAND_EXECUTION_SUCCESSFUL);
}

TEST_CASE("GetAllLines returns all available lines", "[EnergyMeterServiceImpl]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    Empty request;
    AllLinesRequest reply;

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

TEST_CASE("GetModelsByLine returns models for a given line", "[EnergyMeterServiceImpl]")
{
    // Setup
    energy::EnergyMeterServiceImpl service;
    grpc::ServerContext context;
    MeterLine request;
    MeterListRequest reply;

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