#include "apolo.hpp"

namespace ees
{
    Apolo::Apolo(const std::string &model)
        :EnergyMeter(Lines::APOLO, model)
    {
        
    }
} // namespace ees