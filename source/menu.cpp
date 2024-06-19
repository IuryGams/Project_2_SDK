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

    auto Menu::confirm_menu() -> bool
    {
        std::string choice;

        while(true)
        {    
            std::cout << "Digite 'S' para CONFIRMAR ou digite 'N' para CANCELAR.\n";
            getline(std::cin, choice);

            choice = toupper(choice[0]);

            if(choice == "S" || choice == "N")
            {
                break;
            } else {
                std::cout << "Opção inválida. Por gentileza, digite uma opção válida.\n";
            }
        }

        // Return true with selected option is "S" or return false with selected option is "N";
        if(choice == "S") {
            return true;
        } else {
            std::cout << "Ação cancelada!\n";
            return false;
        }
        return (choice == "S");
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
                case 7: create_new_meter();               break;
                case 8: delete_meter(); break;
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
        op.read_meter_list();
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
        int selected_option;
        std::string model_name;

        show_lines_menu();
        selected_option = convert_string_to_int(); 
        std::cout << "Agora informe o nome do modelo desejado: ";
        getline(std::cin, model_name);

        

        switch (selected_option)
        {
            case 1: op.add_new_model(Ares(model_name)); break;
            case 2: op.add_new_model(Apolo(model_name)); break;
            case 3: op.add_new_model(Cronos(model_name)); break;
            case 4: op.add_new_model(Zeus(model_name)); break;
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

        EnergyMeter* meter = op.find_meter_by_id(id);

        if(meter) {
            std::cout << "DADOS ENCONTRADOS -> {\n";
            std::cout << "  Modelo: " << meter->get_model() << std::endl;
            std::cout << "  Linha: " << convert_enumline_to_string(meter->get_line()) << std::endl;
            std::cout << "};\n";
            std::cout << "Deseja excluir esse modelo ?\n";
            if(confirm_menu()) {
                op.remove_model(id);
            } else {
                std::cout << "Ação cancelada!\n";
            }
        }

    }

    void Menu::exit_menu() // Exit Menu.
    {
        std::cout << "Encerrando o sistema..." << std::endl;
    }

}