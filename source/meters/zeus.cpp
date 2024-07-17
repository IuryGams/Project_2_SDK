#include "zeus.hpp"

namespace ees
{
    Zeus::Zeus(const int &id, const std::string &model)
        :EnergyMeter(id, Lines::ZEUS, model)
    {
        
    }
} // namespace ees