#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Apolo : public EnergyMeter
    {
    public:
        Apolo(const std::string &model);
    };
} // namespace ees
