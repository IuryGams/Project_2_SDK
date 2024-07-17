#include "utils.hpp"
#include "operations.hpp"
#include "energy_meter.pb.h"

#include <cstring>
#include <string>
#include <map>

namespace ees
{

    auto convert_enumline_to_string(const ees::Lines &line) -> std::string // Testing OK
    {
        std::map<ees::Lines, std::string> lines_to_string = {
            {ees::Lines::ARES, "ARES"},
            {ees::Lines::APOLO, "APOLO"},
            {ees::Lines::CRONOS, "CRONOS"},
            {ees::Lines::ZEUS, "ZEUS"},
            {ees::Lines::UNKNOWN, "UNKNOWN"},
        };

        return lines_to_string.at(line);
    } // Testing OK

    auto convert_proto_enum_to_cpp_enum(int proto_enum_value) -> ees::Lines // Testing OK
    {
        switch (proto_enum_value)
        {
        case 1:
            return ees::Lines::ARES;
        case 2:
            return ees::Lines::APOLO;
        case 3:
            return ees::Lines::CRONOS;
        case 4:
            return ees::Lines::ZEUS;
        default:
            return ees::Lines::UNKNOWN;
        }
    } // Testing OK

    auto convert_enum_cpp_to_proto_enum(ees::Lines specific_line) -> int
    {
        static std::map<ees::Lines, ::Lines> line_map = {
            {ees::Lines::ARES, ::Lines::ARES},
            {ees::Lines::APOLO, ::Lines::APOLO},
            {ees::Lines::CRONOS, ::Lines::CRONOS},
            {ees::Lines::ZEUS, ::Lines::ZEUS},
        };
        
        auto it = line_map.find(specific_line);

        if (it != line_map.end())
        {
            return it->second;
        }
        else
        {
            return ::Lines::UNKNOWN;
        }
    }

    auto is_all_digits(const std::string &text) -> bool // Testing OK
    {
        for (char c : text)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    auto to_uppercase(const std::string &text) -> std::string // Testing OK
    {
        std::string result = text;

        if(text.empty())
        {
            throw std::runtime_error("Valor inválido!"); 
        }

        for(char & c : result)
        {
            if(std::islower(c))
            {
                c = std::toupper(c);
            }
        }
        return result;
    }
}