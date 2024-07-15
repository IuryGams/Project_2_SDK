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

    // TEST_CASE("Testing function read meter list", "[find_model_by_id]") // OK
    // {
    //     Operations operations;
    //     std::stringstream output;

    //     // Redirect cout
    //     std::streambuf *old_cout = std::cout.rdbuf(output.rdbuf());

    //     operations.read_meter_list();

    //     std::cout.rdbuf(old_cout);

    //     std::string expected_output =
    //         "1 | ARES | 7021\n"
    //         "2 | ARES | 7023\n"
    //         "3 | ARES | 7031\n"
    //         "4 | ARES | 8023\n"
    //         "5 | ARES | 8023 15\n"
    //         "6 | ARES | 8023 200\n"
    //         "7 | CRONOS | 6001-A\n"
    //         "8 | CRONOS | 6021-A\n"
    //         "9 | CRONOS | 6021L\n"
    //         "10 | CRONOS | 6003\n"
    //         "11 | CRONOS | 7023\n"
    //         "12 | CRONOS | 7023L\n"
    //         "13 | CRONOS | 7023 2,5\n"
    //         "14 | APOLO | 6031\n"
    //         "15 | ZEUS | 8021\n"
    //         "16 | ZEUS | 8023\n"
    //         "17 | ZEUS | 8031\n";

    //     REQUIRE(output.str() == expected_output);
    // }

    TEST_CASE("Testing function find model by id", "[find_model_by_id]") // OK
    {
        Operations operations;

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

    TEST_CASE("Testing add new model to meter list", "[find_model_by_id]")
    {
        Operations operations;

        // Scenario 1: add one new model successfully;
        SECTION("add new model successfully")
        {
            Zeus zeus("8071"); // Create one EnergyMeter type Zeus for test.
            bool result;

            operations.add_new_model(zeus);
            int id_zeus = zeus.get_id();

            bool meter_found = false;
            for (auto meter : operations.get_meter_list())
            {
                if (zeus.get_id() == meter.get_id())
                {
                    meter_found = true;
                    break;
                }
            }

            REQUIRE(meter_found);
        }

        // Scenario 2: Try to add a new model that already exists in the list;
        SECTION("Attempt to add existing model")
        {
            Apolo apolo("6001"); // create new Energy Meter type Apolo

            operations.add_new_model(apolo); // add Apolo;

            REQUIRE_FALSE(operations.add_new_model(apolo));
        }
    };

    TEST_CASE("Testing Function delete model")
    {
        Operations operations;

        SECTION("Removes an energy meter that exists in the list and checks if the list has changed")
        {
            int meter_id = operations.get_meter_list().at(1).get_id(); //  Energy Meter get ID;
            bool result = operations.remove_model(meter_id);           // Delete Energy Meter;

            REQUIRE(result); // Expected to be deleted

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
            int meter_id = 20;                         // Create Energy Meter ID does not exist;
            bool result = operations.remove_model(20); // Delete Energy Meter;

            REQUIRE_FALSE(result); // Expected not find Energy Meter;
        }
    }

    TEST_CASE("Check if returned meter list matches expected", "[iury]")
    {
        Operations operations;
        REQUIRE(operations.get_meter_list().size() == 17);
    }

    TEST_CASE("Testing the filter for a selected line", "[find_model_by_id]")
    {
        std::vector<EnergyMeter> test_line;
        Operations operations;

        for (size_t i = 0; i < 3; i++)
        {
            test_line.push_back(Zeus(std::to_string(i + 1000)));
            test_line.push_back(Cronos(std::to_string(i + 1000)));
            test_line.push_back(Ares(std::to_string(i + 1000)));
            test_line.push_back(Apolo(std::to_string(i + 1000)));
        };

        SECTION("Filter objects for line Zeus")
        {
            Lines selected_line = Lines::ZEUS;
            std::vector<EnergyMeter> results = operations.filter_by_line(selected_line);
            REQUIRE(results.size() == 3);

            for (auto &meter : results)
            {
                REQUIRE(meter.get_line() == selected_line);
            };
        }
    };

}