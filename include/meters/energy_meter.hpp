#pragma once

#include "enums.hpp"
#include <string>
#include <vector>

namespace ees
{
    class EnergyMeter
    {
        private:
            static inline int next_id = 0;
            int id;
            ees::Lines line;
            std::string model;

        public:
            EnergyMeter(const int &id, Lines line, const std::string &model);
            auto get_id() const -> int;
            auto get_line() const -> Lines;
            auto get_model() const -> std::string;

            void set_id(const int &id);
            void set_line(const Lines &line);
            void set_model(const std::string &model);

            bool operator==(const EnergyMeter &other) const;
    };
} // namespace ees