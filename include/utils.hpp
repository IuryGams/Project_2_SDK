#pragma once

#include "enums.hpp"
#include "energy_meter.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace ees {
    
    auto convert_enumline_to_string(const Lines &line) -> std::string;
    auto is_all_digits(const std::string &text) -> bool;
    auto convert_proto_enum_to_cpp_enum(int proto_enum_value) -> Lines;
    auto convert_enum_cpp_to_proto_enum(ees::Lines line) -> int;
    auto to_uppercase(const std::string &text) -> std::string;

} // namespace ees