#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Cronos : public EnergyMeter
    {
    public:
        Cronos(const int &id, const std::string &model);
    };
} // namespace ees
