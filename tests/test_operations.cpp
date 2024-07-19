#pragma once
#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"
#include "project_exceptions.hpp"

#include <vector>

ees::Operations operations;

TEST_CASE("Testing function find model by id", "[find_meter_by_id]") // OK
{

    SECTION("Find existing meter by ID"){
        REQUIRE_NOTHROW(operations.find_meter_by_id(5));

        // Verifica se o medidor retornado tem o ID correto
        REQUIRE(operations.find_meter_by_id(5).get_id() == 5);
    }

    SECTION("NOT find meter by ID ")
    {
        // Verifica se uma exceção é lançada quando o medidor não existe
        REQUIRE_THROWS_AS(operations.find_meter_by_id(999), expections::NotFound);
    }
};

TEST_CASE("Testing add new model to meter list", "[add_new_model]"){

    // Scenario 1: add one new model successfully;
    SECTION("add new model successfully"){
        REQUIRE_NOTHROW(operations.add_new_model(ees::EnergyMeter{18, ees::Lines::ARES, "1234"}));
    }

    // Scenario 2: Try to add a new model that already exists in the list;
    SECTION("Attempt to add existing model")
    {
        REQUIRE_THROWS_AS(operations.add_new_model(ees::EnergyMeter{1, ees::Lines::ARES, "1234"}), expections::AlreadyExists);
    }

    SECTION("Throw exception when line is UNKNOWN")
    {
        REQUIRE_THROWS_AS(operations.add_new_model(ees::EnergyMeter{19, ees::Lines::UNKNOWN, "1234"}), expections::NotExists);
    }
};

TEST_CASE("Testing Function delete model")
{
    SECTION("Removes an energy meter that exists in the list and checks if the list has changed")
    {
        REQUIRE(operations.remove_model(1)); // Expected to be deleted
        REQUIRE_THROWS_AS(operations.remove_model(1), expections::NotFound); // Expected not found. Because has deleted;
    }

    SECTION("Throw exception when removing a non-existing meter")
    {
        REQUIRE_THROWS_AS(operations.remove_model(20), expections::NotFound); // Expected not find Energy Meter;
    }
}

TEST_CASE("Check if returned meter list matches expected", "[iury]")
{
    REQUIRE(operations.get_meter_list().size() == 17);
};

TEST_CASE("Testing the filter for a selected line", "[filter_by_line]"){

    SECTION("Filter objects for line Zeus"){
        std::vector<ees::EnergyMeter> results = operations.filter_by_line("Zeus");
        REQUIRE(results.size() == 3);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "ZEUS");
        };
    }

    SECTION("Filter objects for line Ares")
    {
        std::vector<ees::EnergyMeter> results = operations.filter_by_line("Ares");
        REQUIRE(results.size() == 6);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "ARES");
        };
    }

    SECTION("Filter objects for line Cronos")
    {
        std::vector<ees::EnergyMeter> results = operations.filter_by_line("Cronos");
        REQUIRE(results.size() == 7);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "CRONOS");
        };
    }

    SECTION("Filter objects for line Apolo")
    {
        std::vector<ees::EnergyMeter> results = operations.filter_by_line("Apolo");
        REQUIRE(results.size() == 1);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "APOLO");
        };
    }
};