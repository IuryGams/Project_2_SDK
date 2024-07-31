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


TEST_CASE("Check if returned meter list matches expected", "[iury]")
{
    REQUIRE(ees::Operations::get_meter_list().size() == 17);
};

TEST_CASE("Testing add new model to meter list", "[add_new_model]"){

    // Scenario 1: add one new model successfully;
    SECTION("add new model successfully"){
        REQUIRE_NOTHROW(ees::Operations::add_new_model(ees::EnergyMeter{18, ees::Lines::ARES, "1234"}));
    }

    // Scenario 2: Try to add a new model that already exists in the list;
    SECTION("Attempt to add existing model")
    {
        REQUIRE_THROWS_AS(ees::Operations::add_new_model(ees::EnergyMeter{1, ees::Lines::ARES, "1234"}), exceptions::AlreadyExists);
    }

    SECTION("Throw exception when line is UNKNOWN")
    {
        REQUIRE_THROWS_AS(ees::Operations::add_new_model(ees::EnergyMeter{25, ees::Lines::UNKNOWN, "1234"}), exceptions::NotExists);
    }
};


TEST_CASE("Testing Function delete model")
{
    SECTION("Removes an energy meter that exists in the list and checks if the list has changed")
    {
        REQUIRE(ees::Operations::remove_model(18)); // Expected to be deleted
        REQUIRE_THROWS_AS(ees::Operations::remove_model(18), exceptions::NotFound); // Expected not found. Because has deleted;
    }

    SECTION("Throw exception when removing a non-existing meter")
    {
        REQUIRE_THROWS_AS(ees::Operations::remove_model(20), exceptions::NotFound); // Expected not find Energy Meter;
    }
}

TEST_CASE("Testing function find model by id", "[find_meter_by_id]") // OK
{

    SECTION("Find existing meter by ID"){
        REQUIRE_NOTHROW(ees::Operations::find_meter_by_id(5));

        // Verifica se o medidor retornado tem o ID correto
        REQUIRE(ees::Operations::find_meter_by_id(5).get_id() == 5);
    }

    SECTION("NOT find meter by ID ")
    {
        // Verifica se uma exceção é lançada quando o medidor não existe
        REQUIRE_THROWS_AS(ees::Operations::find_meter_by_id(999), exceptions::NotFound);
    }
};

TEST_CASE("Testing the filter for a selected line", "[filter_by_line]"){

    SECTION("Filter objects for line Zeus"){
        std::vector<ees::EnergyMeter> results = ees::Operations::filter_by_line("Zeus");
        REQUIRE(results.size() == 3);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "ZEUS");
        };
    }

    SECTION("Filter objects for line Ares")
    {
        std::vector<ees::EnergyMeter> results = ees::Operations::filter_by_line("Ares");
        REQUIRE(results.size() == 6);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "ARES");
        };
    }

    SECTION("Filter objects for line Cronos")
    {
        std::vector<ees::EnergyMeter> results = ees::Operations::filter_by_line("Cronos");
        REQUIRE(results.size() == 7);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "CRONOS");
        };
    }

    SECTION("Filter objects for line Apolo")
    {
        std::vector<ees::EnergyMeter> results = ees::Operations::filter_by_line("Apolo");
        REQUIRE(results.size() == 1);

        for (auto &meter : results)
        {
            REQUIRE(convert_enumline_to_string(meter.get_line()) == "APOLO");
        };
    }
};

TEST_CASE("Testing function check already exists meter", "[already_exists_meter]")
{
    SECTION("Meter does not exist")
    {
        ees::EnergyMeter meter = ees::EnergyMeter(18, ees::Lines::APOLO, "Model 1");
        REQUIRE(ees::Operations::check_if_meter_already_exists(meter));
    };

    SECTION("Meter already exists")
    {
        REQUIRE_THROWS_AS(ees::Operations::check_if_meter_already_exists(ees::EnergyMeter{2, ees::Lines::APOLO, "Model 1"}), exceptions::AlreadyExists);
    }
}

TEST_CASE("Testing function check already exists line", "[check_if_line_exists]")
{
    std::vector<ees::Lines> list_line = {
        ees::Lines::APOLO,
        ees::Lines::ARES,
        ees::Lines::ZEUS,
        ees::Lines::CRONOS,
        ees::Lines::UNKNOWN};

    SECTION("Line exists")
    {
        REQUIRE(ees::Operations::check_if_line_exists(ees::convert_enumline_to_string(ees::Lines::APOLO)));
    };

    SECTION("Line does not exists")
    {
        REQUIRE_THROWS_AS(ees::Operations::check_if_line_exists("KRATOS"), exceptions::NotExists);
    }
}

TEST_CASE("Testing function check if line is not equal to UNKNOWN", "[check_if_is_unknown]")
{

    SECTION("line is UNKNOWN")
    {
        REQUIRE_THROWS_AS(ees::Operations::check_if_is_unknown("UNKNOWN"), exceptions::NotExists);
    }

    SECTION("line does not UNKNOWN")
    {
        REQUIRE_NOTHROW(ees::Operations::check_if_is_unknown("KRATOS"));
        REQUIRE_NOTHROW(ees::Operations::check_if_is_unknown("Test"));
        REQUIRE_NOTHROW(ees::Operations::check_if_is_unknown(""));
    }
}