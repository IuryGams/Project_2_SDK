#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Zeus : public EnergyMeter
    {
    public:
        Zeus(const int &id, const std::string &model);
    };
} // namespace ees
