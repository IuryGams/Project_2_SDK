#include "operations.hpp"
#include "zeus.hpp"
#include "cronos.hpp"
#include "apolo.hpp"
#include "ares.hpp"
#include "utils.hpp"
#include "menu.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

namespace ees
{
    Menu menu;

    Operations::Operations()
    {
        meter_list =
            {
                Ares("7021"),
                Ares("7023"),
                Ares("7031"),
                Ares("8023"),
                Ares("8023 15"),
                Ares("8023 200"),
                Cronos("6001-A"),
                Cronos("6021-A"),
                Cronos("6021L"),
                Cronos("6003"),
                Cronos("7023"),
                Cronos("7023L"),
                Cronos("7023 2,5"),
                Apolo("6031"),
                Zeus("8021"),
                Zeus("8023"),
                Zeus("8031"),
            };
    }

    auto Operations::get_meter_list() -> std::vector<EnergyMeter>
    {
        return meter_list;
    }

    auto Operations::find_meter_by_id(int &id) -> EnergyMeter*
    {
        auto it = std::find_if(meter_list.begin(), meter_list.end(), [&id](EnergyMeter &meter) 
            {return meter.get_id() == id; } 
        );

        if(it != meter_list.end()) 
        {
            return &(*it);
        } else {
            std::cout << "O medidor de energia com o ID " << id << " não foi encontrado!\n"; // EnergyMeter not found;
            return nullptr;
        }
    }

    auto Operations::filter_by_line(const Lines &line) -> std::vector<EnergyMeter>

    {
        std::vector<EnergyMeter> filtered_meter_list = {}; 
        std::copy_if(meter_list.begin(), meter_list.end(), std::back_inserter(filtered_meter_list),
                     [&line](EnergyMeter meter)
                     { return meter.get_line() == line; });
        return filtered_meter_list;
    }
    
    // CRUD

    auto Operations::add_new_model(const EnergyMeter & new_meter) -> bool // CREATE 
    {
        bool choice;
        
        for(auto meter : meter_list) 
        {
            if(meter.get_model() == new_meter.get_model() && meter.get_line() == new_meter.get_line())
            {
                std::cout << "ERRO: O nome do modelo informado já existe na lista de medidores de energia.\n";
                return false;
            }
        }

        std::cout << "O modelo do medidor é: " << new_meter.get_model() << std::endl;
        std::cout << "O medidor de energia será da linha: " << convert_enumline_to_string(new_meter.get_line()) << std::endl;
        choice = menu.confirm_menu();

        if(choice) {
            meter_list.push_back(new_meter);
            std::cout << "O medidor foi criado com sucesso!\n";
            return true;
        } else {
            return false;
        }
    }

    void Operations::read_meter_list() // READ
    {
        std::cout << "ID" << " | " << "LINHA" << " | " << "MODELO" << std::endl;
        for (EnergyMeter meter : meter_list)
        {
            std::cout << meter.get_id() << " | " << convert_enumline_to_string(meter.get_line()) << " | " << meter.get_model() << std::endl;
        }
    }

    void Operations::update_meter(int &id, Lines &new_line, std::string &new_model) // UPDATE
    {
        EnergyMeter* meter = find_meter_by_id(id);

        if(meter)
        {
            meter->set_line(new_line);
            meter->set_model(new_model);
        };
    }

    auto Operations::remove_model(int id) -> bool // DELETE
    {
        bool choice;
        EnergyMeter* meter = find_meter_by_id(id);

        if(meter) // Checking if the EnergyMeter is found;
        { 
            meter_list.erase(std::remove_if(meter_list.begin(), meter_list.end(), [&id](EnergyMeter &meter) 
                { return meter.get_id() == id; })); // Deleting EnergyMeter found of vector;

            std::cout << "O medido de energia com ID " << meter->get_id() << " foi deletado com sucesso!\n\n";
            return true;
        } 
        std::cout << "ID informado não existe!\n";
        return false;
    }

} // namespace ees