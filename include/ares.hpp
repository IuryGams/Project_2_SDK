#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Ares : public EnergyMeter
    {
    public:
        Ares(const std::string &model);
    };
} // namespace ees
