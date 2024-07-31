#include "operations.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "utils.hpp"
#include "project_exceptions.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

namespace ees
{

    std::vector<EnergyMeter> Operations::meter_list =
    {
        Ares(1, "7021"),
        Ares(2, "7023"),
        Ares(3, "7031"),
        Ares(4, "8023"),
        Ares(5, "8023 15"),
        Ares(6, "8023 200"),
        Cronos(7, "6001-A"),
        Cronos(8, "6021-A"),
        Cronos(9, "6021L"),
        Cronos(10, "6003"),
        Cronos(11, "7023"),
        Cronos(12, "7023L"),
        Cronos(13, "7023 2,5"),
        Apolo(14, "6031"),
        Zeus(15, "8021"),
        Zeus(16, "8023"),
        Zeus(17, "8031"),
    };

    const std::vector<Lines> Operations::lines = {
        Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS, Lines::UNKNOWN
    };

    auto Operations::get_meter_list() -> std::vector<EnergyMeter>
    {
        return meter_list;
    }

    auto Operations::find_meter_by_id(const int &id) -> EnergyMeter
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(),
                               [&id](EnergyMeter &meter)
                               { return meter.get_id() == id; });

        if (it != meter_list.end()) return *it;

        throw exceptions::NotFound{};
    }

    auto Operations::filter_by_line(const std::string &line) -> std::vector<EnergyMeter>
    {
        check_if_line_exists(line);

        std::vector<EnergyMeter> filtered_meter_list;

        std::copy_if(meter_list.begin(), meter_list.end(), std::back_inserter(filtered_meter_list),
                     [&line](EnergyMeter meter)
                     { return convert_enumline_to_string(meter.get_line()) == to_uppercase(line); });
        return filtered_meter_list;
    }

    void Operations::add_new_model(const EnergyMeter &new_meter)
    {
        check_if_meter_already_exists(new_meter);
        check_if_is_unknown(convert_enumline_to_string(new_meter.get_line()));

        // if is not already exists. then, create.
        meter_list.push_back(new_meter);
    }

    auto Operations::remove_model(const int &id) -> bool // DELETE
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(), [id](const EnergyMeter &meter)
                { return meter.get_id() == id; });

        if (it != meter_list.end())
        {
            meter_list.erase(it);
            return true;
        }
        throw exceptions::NotFound{};
    }

    auto Operations::get_all_lines() -> std::vector<Lines>
    {
        return lines;
    }

    auto Operations::check_if_meter_already_exists(const EnergyMeter &new_meter) -> bool
    {
        for (const auto &meter : meter_list )
        {
            if (meter.get_id() == new_meter.get_id()) throw exceptions::AlreadyExists{};
        }
        return true;
    }

    auto Operations::check_if_line_exists(const std::string & line) -> bool
    {
        for(const auto & exists_line : lines)
        {
            if(convert_enumline_to_string(exists_line) == to_uppercase(line)) return true;
        }
        throw exceptions::NotExists{};
    }

    void Operations::check_if_is_unknown(const std::string &line)
    {
        if(line == "UNKNOWN")
        {
            throw exceptions::NotExists{};
        } 
    }
} // namespace ees