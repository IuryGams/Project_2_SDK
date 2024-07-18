#include "validations.hpp"
#include "operations.hpp"
#include "utils.hpp"
#include "project_exceptions.hpp"

namespace ees
{

    Operations operations;

    auto Validations::check_if_meter_already_exists(const EnergyMeter &new_meter) -> bool
    {
        for (const auto &meter : operations.get_meter_list() )
        {
            if (meter.get_id() == new_meter.get_id())
                return true;
        }
        throw expections::AlreadyExists{};
    }

    auto Validations::check_if_line_exists(const std::string & exists_line) -> bool
    {
        for(const auto & line : operations.get_all_lines())
        {
            if(convert_enumline_to_string(line) == exists_line) return true;
        }
        throw expections::NotExists{};
    }

    
}