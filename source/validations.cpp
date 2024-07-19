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
            if (meter.get_id() == new_meter.get_id()) throw expections::AlreadyExists{};
        }
        return true;
    }

    auto Validations::check_if_line_exists(const std::string & line) -> bool
    {
        for(const auto & exists_line : operations.get_all_lines())
        {
            if(convert_enumline_to_string(exists_line) == to_uppercase(line)) return true;
        }
        throw expections::NotExists{};
    }

    void Validations::check_if_is_unknown(const std::string &line)
    {
        if(line == "UNKNOWN")
        {
            throw expections::NotExists{};
        } 
    }
}