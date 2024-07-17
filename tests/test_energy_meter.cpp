#pragma once
#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"

#include <sstream>
#include <vector>

namespace ees {


    TEST_CASE("Setting ID, line and model for EnergyMeter") 
    {
        EnergyMeter meter(1 ,Lines::ARES, "NERO");

        SECTION("Setting ID")
        {
            int ID = 1;
            meter.set_id(ID);

            REQUIRE(meter.get_id() == ID);
        }

        SECTION("Setting line")
        {
            Lines line = Lines::APOLO;
            meter.set_line(line);

            REQUIRE(meter.get_line() == line);
        }

        SECTION("Setting model")
        {
            std::string model = "6921";
            meter.set_model(model);

            REQUIRE(meter.get_model() == model);
        }
    }

    TEST_CASE("test Operator", "[test_operator]")
    {
        EnergyMeter meter(1 ,Lines::ARES, "NERO"); // Example Meter
        EnergyMeter meter2(1 ,Lines::ARES, "NERO"); // Copy of Example Meter;
        EnergyMeter meter3(2 ,Lines::ARES, "NERO"); // ID different to Example Meter;
        EnergyMeter meter4(1 ,Lines::CRONOS, "NERO"); // Line different to Example Meter;
        EnergyMeter meter5(1 ,Lines::ARES, "KRATOS"); // Model different to Example Meter;

        SECTION("The meter is the same")
        {
            REQUIRE(meter == meter2);
        }

        SECTION("Meters with different ids should not be equal")
        {
            REQUIRE_FALSE(meter == meter3);
        }

        SECTION("Meters with different line should not be equal")
        {
            REQUIRE_FALSE(meter == meter4);
        }

        SECTION("Meters with different model should not be equal")
        {
            REQUIRE_FALSE(meter == meter5);
        }
    }
} // namespace ees
