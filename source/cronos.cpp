#include "cronos.hpp"

namespace ees
{
    Cronos::Cronos(const std::string &model)
        :EnergyMeter(Lines::CRONOS, model)
    {
        
    }
} // namespace ees