#pragma once

#include "enums.hpp"
#include "energy_meter.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace ees {
    
    auto convert_enumline_to_string(const Lines &line) -> std::string;
    auto is_all_digits(const std::string &text) -> bool;
    auto convert_string_to_int() -> int;
    auto convert_proto_enum_to_cpp_enum(int proto_enum_value) -> Lines;
    auto convert_to_proto_enum(Lines line) -> int;
    auto to_uppercase(std::string &text) -> std::string;



} // namespace ees