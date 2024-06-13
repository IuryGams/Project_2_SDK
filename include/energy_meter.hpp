#pragma once

#include "enums.hpp"
#include <string>
#include <vector>

namespace ees
{
    class EnergyMeter
    {
        private:
            static int next_id;
            int id;
            Lines line;
            std::string model;

        public:
            EnergyMeter(Lines line, const std::string &model);
            auto get_id() -> int;
            auto get_line() -> Lines;
            auto get_model() -> std::string;

            void set_line(const Lines &line);
            void set_model(const std::string &model);
    };
} // namespace ees