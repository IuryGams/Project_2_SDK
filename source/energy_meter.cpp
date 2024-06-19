#include "energy_meter.hpp"
#include <vector>

namespace ees
{
    int EnergyMeter::next_id = 1;

    EnergyMeter::EnergyMeter(Lines line, const std::string &model) : id(next_id++), line(line), model(model) {};

    int EnergyMeter::get_id() const
    {
        return id;
    }
    Lines EnergyMeter::get_line() const
    {
        return line;
    }
    std::string EnergyMeter::get_model() const
    {
        return model;
    }
    void EnergyMeter::set_line(const Lines &line)
    {
        this->line = line;
    }
    void EnergyMeter::set_model(const std::string &model)
    {
        this->model = model;
    }

}; // namespace ees