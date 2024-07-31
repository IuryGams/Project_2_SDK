#pragma once

#include "energy_meter.hpp"
#include "enums.hpp"
#include <variant>

namespace ees
{
    class Operations
    {
    private:
        static std::vector<EnergyMeter> meter_list;
        static const std::vector<Lines> lines;


    public:
        static auto check_if_meter_already_exists(const EnergyMeter &meter) -> bool;
        static auto check_if_line_exists(const std::string &line) -> bool;
        static void check_if_is_unknown(const std::string &line);
        static auto get_meter_list() -> std::vector<EnergyMeter>;

        static auto filter_by_line(const std::string &line) -> std::vector<EnergyMeter>;
        
        static auto get_all_lines() -> std::vector<Lines>;
        static auto find_meter_by_id(const int &id) -> EnergyMeter;

        // CRUD
        static void add_new_model(const EnergyMeter & new_meter);
        static auto remove_model(const int &id) -> bool;
    };
} // namespace ees
