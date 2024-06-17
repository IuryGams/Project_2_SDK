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
        auto filter_by_line(std::vector<EnergyMeter> &energy_meters, const Lines &line) -> std::vector<EnergyMeter>;
        auto find_meter_by_id(int &id) -> EnergyMeter*;

        // CRUD
        void add_new_model(const EnergyMeter & new_meter); // CREATE
        void read_meter_list(); // READ
        void update_meter(int &id, Lines &new_line, std::string &new_model); // UPDATE
        void remove_model(int id); // DELETE
    };
    
} // namespace ees
