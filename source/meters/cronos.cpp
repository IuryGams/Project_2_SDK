#include "cronos.hpp"

namespace ees
{
    Cronos::Cronos(const int &id, const std::string &model)
        :EnergyMeter(id, Lines::CRONOS, model)
    {
        
    }
} // namespace ees