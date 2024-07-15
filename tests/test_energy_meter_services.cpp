#pragma once
#include "catch.hpp"
#include "energy_meter.grpc.pb.h"
#include "energy_meter_services.hpp"
#include "energy_meter.hpp"
#include <grpcpp/grpcpp.h>
#include "operations.hpp"

TEST_CASE("CreateMeter Test", "[grpc]") {
    // Setup
    ees::Operations operations;
    energy::EnergyMeterServiceImpl service;

    grpc::ServerContext context;
    MeterInfor request;
    MeterCompleteInfor reply;

    request.set_line(Lines::ARES); // Defina os valores apropriados para a linha e o modelo
    request.set_model("Modelo exemplo");

    SECTION("Successfully create a new meter") {
        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.ok());
        REQUIRE(reply.id() != 0); // Verifique se o ID foi definido corretamente
        REQUIRE(reply.line() == request.line());
        REQUIRE(reply.model() == request.model());
    }

    SECTION("Meter already exists") {
        // Adicione um medidor existente na lista
        ees::EnergyMeter existing_meter(static_cast<ees::Lines>(request.line()), request.model());
        operations.add_new_model(existing_meter);

        grpc::Status status = service.CreateMeter(&context, &request, &reply);

        REQUIRE(status.error_code() == grpc::ALREADY_EXISTS);
        REQUIRE(status.error_message() == "Medidor já existe");
    }
}