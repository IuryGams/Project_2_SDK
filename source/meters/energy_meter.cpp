#include "energy_meter.hpp"
#include <vector>

namespace ees
{
    EnergyMeter::EnergyMeter(const int &id, Lines line, const std::string &model) : id(id), line(line), model(model) {}

    bool EnergyMeter::operator==(const EnergyMeter & other) const
    {
        return this->get_id() == other.get_id() && this->get_line() == other.get_line() && this->get_model() == other.get_model();
    }

    int EnergyMeter::get_id() const { return id; }

    Lines EnergyMeter::get_line() const { return line; }

    std::string EnergyMeter::get_model() const { return model; }

    void EnergyMeter::set_id(const int &id) { this->id = id; }

    void EnergyMeter::set_line(const Lines &line) { this->line = line; }

    void EnergyMeter::set_model(const std::string &model) { this->model = model; }

}; // namespace ees