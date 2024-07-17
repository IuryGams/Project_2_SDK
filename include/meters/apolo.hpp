#pragma once

#include "energy_meter.hpp"

namespace ees
{
    class Apolo : public EnergyMeter
    {
    public:
        Apolo(const int &id,const std::string &model);
    };
} // namespace ees
