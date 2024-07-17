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
    Operations::Operations()
    {
        meter_list =
            {
                Ares(1,"7021"),
                Ares(2,"7023"),
                Ares(3,"7031"),
                Ares(4,"8023"),
                Ares(5,"8023 15"),
                Ares(6,"8023 200"),
                Cronos(7,"6001-A"),
                Cronos(8,"6021-A"),
                Cronos(9,"6021L"),
                Cronos(10,"6003"),
                Cronos(11,"7023"),
                Cronos(12,"7023L"),
                Cronos(13,"7023 2,5"),
                Apolo(14,"6031"),
                Zeus(15,"8021"),
                Zeus(16,"8023"),
                Zeus(17,"8031"),
            };
    }

    auto Operations::get_meter_list() -> std::vector<EnergyMeter>
    {
        return meter_list;
    }

    auto Operations::find_meter_by_id(const int &id) -> EnergyMeter
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(),
         [&id](EnergyMeter &meter)
        { return meter.get_id() == id; });

        if (it != meter_list.end())
        {
            return *it;
        }

        throw ees::NotFound{};
    }

    auto Operations::filter_by_line(const Lines &line) -> std::vector<EnergyMeter>
    {
        std::vector<EnergyMeter> filtered_meter_list;

        std::copy_if(meter_list.begin(), meter_list.end(), std::back_inserter(filtered_meter_list),
                     [&line](EnergyMeter meter)
                     { return meter.get_line() == line; });
        return filtered_meter_list;
    }

    auto Operations::filter_by_line(const std::string &line) -> std::vector<EnergyMeter>
    {
        std::vector<EnergyMeter> filtered_meter_list;

        std::copy_if(meter_list.begin(), meter_list.end(), std::back_inserter(filtered_meter_list),
                     [&line](EnergyMeter meter)
                     { return convert_enumline_to_string(meter.get_line()) == line; });
        return filtered_meter_list;
    }

    auto Operations::check_if_meter_already_exists(const EnergyMeter &new_meter) -> bool
    {
        for (const auto &meter : meter_list)
        {
            if (meter.get_id() == new_meter.get_id())
            {   
                return false; // meter already exists;
            }
        }
        throw ees::ThisMeterAlreadyExist{};
    }

    auto Operations::add_new_model(const EnergyMeter &new_meter) -> bool
    {
        if (check_if_meter_already_exists(new_meter))
        {
            meter_list.push_back(new_meter);
            return true;
        }
        return false;
    }

    auto Operations::remove_model(const int &id) -> bool // DELETE
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(), [id](const EnergyMeter &meter)
                               { return meter.get_id() == id; });

        if (it != meter_list.end())
        {
            meter_list.erase(it); // Remove  o medidor encontrado
            return true;
        }
        throw ees::NotFound{};
    }

    auto Operations::get_all_lines() -> std::vector<Lines>
    {
        return {Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS, Lines::UNKNOWN};
    }
} // namespace ees