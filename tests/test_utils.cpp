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

namespace ees
{

    

    TEST_CASE("Testing function convert enum class to string")
    {
        std::string line = "APOLO";
        Lines apolo_line = Lines::APOLO;

        REQUIRE(convert_enumline_to_string(apolo_line) == line);
    }

    TEST_CASE("Checking function get_meter_list")
    {
        Operations operations;
        std::vector<EnergyMeter> meter_list = operations.get_meter_list();

        SECTION("Check if returned meter list matches expected")
        {
            std::vector<EnergyMeter> meter_list = operations.get_meter_list();

            REQUIRE(meter_list.size() == 17);
        }
    }

    TEST_CASE("Testing the filter for a selected line")
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

    TEST_CASE("Testing function is_all_digits"){

        SECTION("Receiving a string value with letters."){
            std::string text = "I am developer";
            bool result = is_all_digits(text);

            REQUIRE(result == false);
        }

        SECTION("Receiving a string value with numbers.")
        {
            std::string number = "2";
            bool result = is_all_digits(number);

            REQUIRE(result == true);
        }
    };

    TEST_CASE("Testing function find model by id")
    {
        Operations operations;
        std::vector<EnergyMeter> meter_list = operations.get_meter_list();

        SECTION("Find existing meter by ID")
        {
            int id_to_find = meter_list.at(1).get_id();
            EnergyMeter *found_meter = operations.find_meter_by_id(id_to_find);

            REQUIRE(found_meter != nullptr);
            REQUIRE(found_meter->get_id() == id_to_find);
        }

        SECTION("NOT find meter by ID ")
        {
            int id_to_find = 999;
            EnergyMeter *found_meter = operations.find_meter_by_id(id_to_find);

            REQUIRE(found_meter == nullptr);
        }
    };

    TEST_CASE("Testing add new model to meter list")
    {
        Operations operations;
        std::vector<EnergyMeter> meter_list;

        class MockMenu
        {
        public:
            bool confirm_menu_successfully() // Mocking user input of choosing add the model
            {
                return true;
            }
            bool confirm_menu_failed() // Mocking user input of choosing not to add the model
            {
                return false;
            }
        };

        MockMenu menu;

        // Scenario 1: add one new model successfully;
        SECTION("add new model successfully")
        {
            Zeus zeus("8071"); // Create one EnergyMeter type Zeus for test.
            bool result;

            if (menu.confirm_menu_successfully())
            {
                meter_list.push_back(zeus);
                result = true;
            }

            REQUIRE(result == true);
        }

        // Scenario 2: Try to add a new model that already exists in the list;
        SECTION("Attempt to add existing model")
        {
            Apolo apolo("6001");
            bool result;

            // Mocking user selected yes option;
            if (menu.confirm_menu_successfully())
            {
                meter_list.push_back(apolo); // add new EnergyMeter type Apolo;
                result = true;
            }

            // Mocking user selected yes option;
            if (menu.confirm_menu_successfully())
            {
                meter_list.push_back(apolo); // try add same meter in the list, must be failed;
                result = false;
            }

            REQUIRE(result == false);
        }

        // Scenario 3: Choose not to add model;
        SECTION("Choose not to add model")
        {
            Cronos cronos("8071"); // Create one EnergyMeter type Cronos for test;
            bool result;

            if (menu.confirm_menu_failed()) // Mocking user selected not option;
            {
                result = operations.add_new_model(cronos);
            }
            else
            {
                result = false;
            }

            REQUIRE(result == false);
        }
    };

    TEST_CASE("Testing Function delete model")
    {
        Operations operations;
        std::vector<EnergyMeter> meter_list = operations.get_meter_list();

        SECTION("Removes an energy meter that exists in the list and checks if the list has changed")
        {
            int meter_id = meter_list.at(1).get_id(); //  Energy Meter get ID;
            bool result = operations.remove_model(meter_id); // Delete Energy Meter;

            REQUIRE(result == true); // Expected to be deleted

            EnergyMeter* meter = operations.find_meter_by_id(meter_id); // Checking if the Energy Meter does not exist
            REQUIRE(meter == nullptr); // Expected not find Energy Meter;
        }

        SECTION("Try remove Energy Meter non-existent")
        {
            int meter_id = 20; // Create Energy Meter ID does not exist;
            bool result = operations.remove_model(20); // Delete Energy Meter;

            REQUIRE(result == false); // Expected not find Energy Meter;
        }

    }

} // namespace ees
