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


    TEST_CASE("Setting line and model for EnergyMeter") 
    {
        EnergyMeter meter(Lines::ARES, "NERO");

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
} // namespace ees
