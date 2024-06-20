#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Zeus : public EnergyMeter
    {
    public:
        Zeus(const std::string &model);
    };
} // namespace ees
