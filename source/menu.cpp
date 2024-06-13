#include "menu.hpp"
#include "operations.hpp"
#include "enums.hpp"
#include "utils.hpp"

#include <vector>
#include <cstring>

namespace ees
{
    Operations op;

    void Menu::show_start_menu() // Start Menu.
    {
        std::cout << "Selecione uma opção do menu.\n";
        std::cout << "1 - Mostrar todas as linhas.\n";
        std::cout << "2 - Mostrar modelos de medidores de energia.\n";
        std::cout << "3 - Mostrar linha Ares.\n";
        std::cout << "4 - Mostrar linha Apolo.\n";
        std::cout << "5 - Mostrar linha Cronos.\n";
        std::cout << "6 - Mostrar linha Zeus.\n";
        std::cout << "7 - Adicionar um modelo a uma linha.\n";
        std::cout << "8 - Excluir um modelo.\n";
        std::cout << "9 - Sair. \n\n";
    }

    void Menu::run_menu() // Select option menu.
    {
        int option;
        do {
            show_start_menu();
            option = read_option_menu();
            switch (option)
            {
                case 1: show_all_lines(); break;
                case 2: show_all_models(); break;
                case 3: show_line(Lines::ARES); break;
                case 4: show_line(Lines::APOLO); break;
                case 5: show_line(Lines::CRONOS); break;
                case 6: show_line(Lines::ZEUS); break;
                case 7: add_model_to_specific_line(); break;
                case 8: delete_model(); break;
                case 9: exit_menu(); break;
                default:
                    std::cout << "O menu não reconheceu o digito informado. Por gentileza, insira um digito de 1 a 9. \n\n";
                    break;
            };
        } while (option != 9);
    }

    void Menu::show_all_lines() // Show all lines
    {
        std::cout << std::endl;
        std::vector<Lines> lines = {Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS};
        for (size_t i = 0; i < lines.size(); i++)
        {
            std::cout << "Linha: " << convert_enumline_to_string(lines.at(i)) << "\n";
        }
    }

    void Menu::show_all_models() // Show all models
    {
        op.read_meter_list();
        std::cout << std::endl;
    }

    void Menu::show_line(const Lines &name_line) // Show a specific line
    {
        std::vector<EnergyMeter> list_of_energy_meters = op.get_meter_list(); // Returning all models.
        std::vector<EnergyMeter> found_list_line = filter_by_line(list_of_energy_meters, name_line); // Returning a selected line.
        
        // Show selected Line.
        std::cout << "Segue abaixo a lista de modelos da linha " << convert_enumline_to_string(found_list_line.at(0).get_line()) << ".\n";
        for (EnergyMeter selectedline : found_list_line)
        {
            std::cout << "ID: " << selectedline.get_id() << " - " << convert_enumline_to_string(selectedline.get_line()) << " " << selectedline.get_model() << std::endl;
        };
    };

    void Menu::add_model_to_specific_line() 
    {
        Lines specific_line;
        std::string new_model;
        std::vector<EnergyMeter> list_energy_meters = op.get_meter_list();
        add_model_to_line(list_energy_meters, specific_line, new_model);
    }

    void Menu::delete_model() 
    {
        int selected_id;
        std::vector<EnergyMeter> list_energy_meters = op.get_meter_list();
        std::cout << "Digite o ID do modelo que deseja excluir.\n";
        std::cin >> selected_id;
        delete_by_id(list_energy_meters, selected_id);
        for(size_t i = 0; i < list_energy_meters.size(); i++) {
            std::cout << "ID: " << list_energy_meters.at(i).get_id() << std::endl;
        }
    }

    void Menu::exit_menu() // Exit Menu.
    {
        std::cout << "Encerrando o sistema..." << std::endl;
    }

}