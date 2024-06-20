#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Operations
    {
    private:
        std::vector<EnergyMeter> meter_list;
    public:
        Operations();
        auto get_meter_list() -> std::vector<EnergyMeter>;
        auto filter_by_line(const Lines &line) -> std::vector<EnergyMeter>;
        auto find_meter_by_id(int &id) -> EnergyMeter;
        auto check_if_meter_already_exists(const EnergyMeter &meter) -> bool;

        // CRUD
        auto add_new_model(const EnergyMeter & new_meter) -> bool; // CREATE
        auto remove_model(int id) -> bool; // DELETE
    };
    
} // namespace ees
