#include "catch.hpp"
#include "utils.hpp"
#include "enums.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "operations.hpp"

#include <vector>

// auto filter_by_line(std::vector<EnergyMeter> &energy_meters,const Lines &line) -> std::vector<EnergyMeter>;

namespace ees
{

    TEST_CASE("Testing function convert enum class to string")
    {
        REQUIRE(convert_enumline_to_string(Lines::APOLO) == "APOLO" );    
    }

    TEST_CASE("Testing the filter for a selected line")
    {
        std::vector<EnergyMeter> test_line;

        for (size_t i = 0; i < 3; i++)
        {
            test_line.push_back(Zeus(std::to_string(i + 1000)));
            test_line.push_back(Cronos(std::to_string(i + 1000)));
            test_line.push_back(Ares(std::to_string(i + 1000)));
            test_line.push_back(Apolo(std::to_string(i + 1000)));
        };

        SECTION("Filter objects for line Zeus") 
        {
            Operations op;
            Lines selected_line = Lines::ZEUS;
            std::vector<EnergyMeter> results = op.filter_by_line(test_line, selected_line);
            REQUIRE(results.size() == 3);

            for(auto &meter : results) {
                REQUIRE(meter.get_line() == selected_line);
            };
        }
    }

    TEST_CASE("Testing function is_all_digits") {
        std::string text = "I am developer";

        REQUIRE(is_all_digits(text) == false);   
    }

} // namespace ees
