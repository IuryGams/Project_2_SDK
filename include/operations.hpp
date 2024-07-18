#pragma once

#include "energy_meter.hpp"
#include "enums.hpp"
#include <variant>

namespace ees
{
    class Operations
    {
    private:
        std::vector<EnergyMeter> meter_list;
    public:
        Operations();
        auto get_meter_list() -> std::vector<EnergyMeter>;

        auto filter_by_line(const std::string &line) -> std::vector<EnergyMeter>;
        
        auto get_all_lines() -> std::vector<Lines>;
        auto find_meter_by_id(const int &id) -> EnergyMeter;

        // CRUD
        void add_new_model(const EnergyMeter & new_meter);
        auto remove_model(const int &id) -> bool;
    };
} // namespace ees
