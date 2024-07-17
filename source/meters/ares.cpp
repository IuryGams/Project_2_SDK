#include "ares.hpp"

namespace ees
{
    Ares::Ares(const int &id, const std::string &model)
        :EnergyMeter(id,Lines::ARES, model)
    {
        
    }
} // namespace ees