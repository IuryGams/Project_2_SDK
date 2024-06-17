#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Operations
    {
    private:
        static std::vector<EnergyMeter> meter_list;
    public:
        Operations();
        void add_new_meter(const EnergyMeter &meter);
        auto get_meter_list() -> std::vector<EnergyMeter>;
        void read_meter_list();
        auto filter_by_line(std::vector<EnergyMeter> &energy_meters, const Lines &line) -> std::vector<EnergyMeter>;
        void add_new_model(std::vector<EnergyMeter> &energy_meters, Lines line, std::string model);
        static auto remove_model(std::vector<EnergyMeter> &meters, int id) -> bool;
    };
    
} // namespace ees
