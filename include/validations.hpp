#pragma once

#include "energy_meter.hpp"
#include <string>


namespace ees 
{

    class Validations
    {
        public:
        auto check_if_meter_already_exists(const EnergyMeter &meter) -> bool;
        auto check_if_line_exists(const std::string &exists_line) -> bool;

    };
}