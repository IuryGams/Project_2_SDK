#include "operations.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "utils.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

namespace ees
{
    Menu menu;

    Operations::Operations()
    {
        meter_list =
            {
                Ares("7021"),
                Ares("7023"),
                Ares("7031"),
                Ares("8023"),
                Ares("8023 15"),
                Ares("8023 200"),
                Cronos("6001-A"),
                Cronos("6021-A"),
                Cronos("6021L"),
                Cronos("6003"),
                Cronos("7023"),
                Cronos("7023L"),
                Cronos("7023 2,5"),
                Apolo("6031"),
                Zeus("8021"),
                Zeus("8023"),
                Zeus("8031"),
            };
    }

    auto Operations::get_meter_list() -> std::vector<EnergyMeter>
    {
        return meter_list;
    }

    auto Operations::find_meter_by_id(const int &id) -> EnergyMeter
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(), [&id](EnergyMeter &meter)
                               { return meter.get_id() == id; });

        if (it != meter_list.end())
        {
            return *it;
        }
        else
        {
            throw std::runtime_error("Medidor de energia não encontrado.");
        }
    }

    auto Operations::filter_by_line(const Lines &line) -> std::vector<EnergyMeter>
    {
        std::vector<EnergyMeter> filtered_meter_list = {};
        std::copy_if(meter_list.begin(), meter_list.end(), std::back_inserter(filtered_meter_list),
                     [&line](EnergyMeter meter)
                     { return meter.get_line() == line; });
        return filtered_meter_list;
    }

    auto Operations::check_if_meter_already_exists(const EnergyMeter &new_meter) -> bool
    {
        for (auto meter : meter_list)
        {
            if (meter.get_model() == new_meter.get_model() && meter.get_line() == new_meter.get_line())
            {
                return false;
            }
        }
        return true;
    }

    auto Operations::add_new_model(const EnergyMeter &new_meter) -> bool // CREATE
    {
        if (check_if_meter_already_exists(new_meter))
        {
            meter_list.push_back(new_meter);
            return true;
        }
        else
        {
            return false;
        }
    }

    auto Operations::remove_model(int id) -> bool // DELETE
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(), [id](const EnergyMeter &meter)
                               { return meter.get_id() == id; });

        if (it != meter_list.end())
        {
            meter_list.erase(it); // Remove  o medidor encontrado
            return true;
        }
        else
        {
            return false; // Medidor não encontrado
        }
    }

    auto Operations::get_all_lines() -> std::vector<Lines>
    {
        return {Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS, Lines::UNKNOWN};
    }
} // namespace ees