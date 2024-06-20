#include "menu.hpp"
#include "operations.hpp"
#include "enums.hpp"
#include "utils.hpp"
#include "ares.hpp"
#include "apolo.hpp"
#include "cronos.hpp"
#include "zeus.hpp"

#include <vector>
#include <cstring>
#include <string>
#include <iostream>

namespace ees
{
    Operations op;

    void Menu::show_inicial_menu() // Start Menu.
    {
        std::cout << "Selecione uma opção do menu.\n";
        std::cout << "1 - Mostrar todas as linhas.\n";
        std::cout << "2 - Mostrar todos os modelos de medidores de energia.\n";
        std::cout << "3 - Mostrar linha Ares.\n";
        std::cout << "4 - Mostrar linha Apolo.\n";
        std::cout << "5 - Mostrar linha Cronos.\n";
        std::cout << "6 - Mostrar linha Zeus.\n";
        std::cout << "7 - Adicionar um novo modelo.\n";
        std::cout << "8 - Remover um modelo.\n";
        std::cout << "9 - Sair. \n\n";

        std::cout << "Informe o dígito: ";
    }

    void Menu::show_lines_menu()
    {
        std::vector<Lines> lines = {Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS};
        int it = 1;
        std::cout << "Selecione uma linha para adicionar um novo modelo.\n";
        for (auto line : lines)
        {
            std::cout << it << " - adicionar a linha " << convert_enumline_to_string(line) << ".\n";
            it++;
        }
        std::cout << "Informe o digito: ";
    }

    void Menu::run_menu() // Select option menu.
    {
        int option;
        do {
            show_inicial_menu();
            option = convert_string_to_int();
            switch (option)
            {
                case 1: show_all_lines();                   break;
                case 2: show_all_models();                  break;
                case 3: show_line(Lines::ARES);             break;
                case 4: show_line(Lines::APOLO);            break;
                case 5: show_line(Lines::CRONOS);           break;
                case 6: show_line(Lines::ZEUS);             break;
                case 7: create_new_meter();                 break;
                case 8: delete_meter();                     break;
                case 9: exit_menu();                        break;
                default:
                    std::cout << "O menu não reconheceu o digito informado. Por gentileza, insira um digito de 1 a 9. \n\n";
                    break;
            };
        } while (option != 9);
    }

    void Menu::show_all_lines() // Show all lines;
    {
        std::cout << std::endl;
        std::vector<Lines> lines = {Lines::ARES, Lines::APOLO, Lines::CRONOS, Lines::ZEUS};
        for (auto line : lines)
        {
            std::cout << "Linha: " << convert_enumline_to_string(line) << "\n";
        }
    }

    void Menu::show_all_models() // Show all models
    {
        std::cout << "ID" << " | " << "LINHA" << " | " << "MODELO" << std::endl;
        for (auto &meter : op.get_meter_list())
        {
            std::cout << meter.get_id() << " | " << convert_enumline_to_string(meter.get_line()) << " | " << meter.get_model() << std::endl;
        }
        std::cout << std::endl;
    }

    void Menu::show_line(const Lines &name_line) // Show a specific line
    {
        std::vector<EnergyMeter> list_of_energy_meters = op.get_meter_list(); // Returning all models.
        std::vector<EnergyMeter> found_list_line = op.filter_by_line(name_line); // Returning a selected line.
        
        // Show selected Line.
        std::cout << "Segue abaixo a lista de modelos da linha " << convert_enumline_to_string(found_list_line.at(0).get_line()) << ".\n";
        for (EnergyMeter selectedline : found_list_line)
        {
            std::cout << "ID: " << selectedline.get_id() << " - " << convert_enumline_to_string(selectedline.get_line()) << " " << selectedline.get_model() << std::endl;
        };
    };

    void Menu::create_new_meter() 
    {
        show_lines_menu();
        std::string model_name;

        int selected_option = convert_string_to_int(); 
        std::cout << "Agora informe o nome do modelo desejado: ";
        getline(std::cin, model_name);

        switch (selected_option)
        {
            case 1: op.add_new_model(Ares(model_name)) ? std::cout << "Modelo criado!\n" : std::cout << "Não foi possivel criar o modelo\n"; break;
            case 2: op.add_new_model(Apolo(model_name)) ? std::cout << "Modelo criado!\n" : std::cout << "Não foi possivel criar o modelo\n"; break;
            case 3: op.add_new_model(Cronos(model_name)) ? std::cout << "Modelo criado!\n" : std::cout << "Não foi possivel criar o modelo\n"; break;
            case 4: op.add_new_model(Zeus(model_name)) ? std::cout << "Modelo criado!\n" : std::cout << "Não foi possivel criar o modelo\n"; break;
        default:
            std::cout << "Opção inválida.\n";
            break;
        }
    }

    void Menu::delete_meter()
    {
        int id;
        std::cout << "Digite o ID do modelo: ";
        id = convert_string_to_int();

        op.remove_model(id) ? std::cout << "Modelo deletado com sucesso!\n" : std::cout << "Não foi possivel deletar o modelo.\n";
    }

    void Menu::exit_menu() // Exit Menu.
    {
        std::cout << "Encerrando o sistema..." << std::endl;
    }

}