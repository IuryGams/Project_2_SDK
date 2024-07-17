#include "apolo.hpp"

namespace ees
{
    Apolo::Apolo(const int &id, const std::string &model)
        :EnergyMeter(id,Lines::APOLO, model)
    {
        
    }
} // namespace ees