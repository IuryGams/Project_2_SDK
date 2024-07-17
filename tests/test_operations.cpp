#pragma once
#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"

#include <vector>
#include <sstream>

namespace ees
{
    Operations operations;

    TEST_CASE("Testing function find model by id", "[find_meter_by_id]") // OK
    {

        SECTION("Find existing meter by ID")
        {
            const int id = 5; // ID de um medidor que existe na lista

            REQUIRE_NOTHROW(operations.find_meter_by_id(id));

            // Verifica se o medidor retornado tem o ID correto
            REQUIRE(operations.find_meter_by_id(id).get_id() == id);
        }

        SECTION("NOT find meter by ID ")
        {
            const int id = 999; // ID de um medidor que NÃO existe na lista

            // Verifica se uma exceção é lançada quando o medidor não existe
            REQUIRE_THROWS_AS(operations.find_meter_by_id(id), std::runtime_error);
        }
    };   

    TEST_CASE("Testing add new model to meter list", "[add_new_model]")
    {

        // Scenario 1: add one new model successfully;
        SECTION("add new model successfully")
        {
            Zeus zeus(18,"8071"); // Create one EnergyMeter type Zeus for test.

            REQUIRE(operations.add_new_model(zeus));
        }

        // Scenario 2: Try to add a new model that already exists in the list;
        SECTION("Attempt to add existing model")
        {
            Apolo apolo(1,"6001"); // create new Energy Meter type Apolo

            operations.add_new_model(apolo); // add Apolo;

            REQUIRE_FALSE(operations.add_new_model(apolo));
        }
    };

    TEST_CASE("Testing Function delete model")
    {

        SECTION("Removes an energy meter that exists in the list and checks if the list has changed")
        {
            int meter_id = operations.get_meter_list().at(1).get_id(); //  Energy Meter get ID;

            REQUIRE(operations.remove_model(meter_id)); // Expected to be deleted

            bool meter_found = false;
            for (auto &meter : operations.get_meter_list()) // Checking if the Energy Meter does not exist
            {
                if (meter.get_id() == meter_id)
                {
                    meter_found = true;
                    break;
                }
            }
            REQUIRE_FALSE(meter_found); // Expected not find Energy Meter;
        }

        SECTION("Try remove Energy Meter non-existent")
        {
            REQUIRE_FALSE(operations.remove_model(20)); // Expected not find Energy Meter;
        }
    }

    TEST_CASE("Check if returned meter list matches expected", "[iury]")
    {
        REQUIRE(operations.get_meter_list().size() == 17);
    }

    TEST_CASE("Testing the filter for a selected line", "[filter_by_line]")
    {

        SECTION("Filter objects for line Zeus")
        {
            std::vector<EnergyMeter> results = operations.filter_by_line(Lines::ZEUS);
            REQUIRE(results.size() == 3);

            for (auto &meter : results)
            {
                REQUIRE(meter.get_line() == Lines::ZEUS);
            };
        }

        SECTION("Filter objects for line Ares")
        {
            std::vector<EnergyMeter> results = operations.filter_by_line(Lines::ARES);
            REQUIRE(results.size() == 4);

            for (auto &meter : results)
            {
                REQUIRE(meter.get_line() == Lines::ARES);
            };
        }

        SECTION("Filter objects for line Cronos")
        {
            std::vector<EnergyMeter> results = operations.filter_by_line(Lines::CRONOS);
            REQUIRE(results.size() == 6);

            for (auto &meter : results)
            {
                REQUIRE(meter.get_line() == Lines::CRONOS);
            };
        }

        SECTION("Filter objects for line Apolo")
        {
            std::vector<EnergyMeter> results = operations.filter_by_line(Lines::APOLO);
            REQUIRE(results.size() == 1);

            for (auto &meter : results)
            {
                REQUIRE(meter.get_line() == Lines::APOLO);
            };
        }
    };

}