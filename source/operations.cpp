#include "operations.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "utils.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

namespace ees
{
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

    void Operations::add_new_meter(const EnergyMeter &meter)
    {
        meter_list.push_back(meter);
    }

    auto Operations::get_meter_list() -> std::vector<EnergyMeter>
    {
        return meter_list;
    }

    void Operations::read_meter_list()
    {
        std::cout << "ID" << " | " << "LINHA" << " | " << "MODELO" << std::endl;
        for (int i = 0; i < meter_list.size(); i++)
        {
            std::cout << meter_list.at(i).get_id() << " | " << convert_enumline_to_string(meter_list.at(i).get_line()) << " | " << meter_list.at(i).get_model() << std::endl;
        }
    }

    auto Operations::filter_by_line(std::vector<EnergyMeter> &energy_meters, const Lines &line) -> std::vector<EnergyMeter>
    {
        std::vector<EnergyMeter> filtered_meter_list = {};
        std::copy_if(energy_meters.begin(), energy_meters.end(), std::back_inserter(filtered_meter_list),
                     [line](EnergyMeter meter)
                     { return meter.get_line() == line; });
        return filtered_meter_list;
    }

} // namespace ees