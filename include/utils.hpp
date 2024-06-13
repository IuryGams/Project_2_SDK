#pragma once

#include "enums.hpp"
#include "energy_meter.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace ees {
    
    auto convert_enumline_to_string(const Lines &line) -> std::string;
    auto is_all_digits(const std::string &text) -> bool;
    auto read_option_menu() -> int;



} // namespace ees