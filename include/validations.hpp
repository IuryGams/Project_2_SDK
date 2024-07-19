#pragma once

#include "energy_meter.hpp"
#include <string>


namespace ees 
{

    class Validations
    {
        public:
        auto check_if_meter_already_exists(const EnergyMeter &meter) -> bool;
        auto check_if_line_exists(const std::string &line) -> bool;
        void check_if_is_unknown(const std::string &line );
    };
}